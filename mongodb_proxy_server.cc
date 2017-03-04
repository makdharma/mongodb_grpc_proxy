#include <assert.h>
#include <string>

#include <google/protobuf/util/json_util.h>
#include <grpc++/grpc++.h>

#include "mongo_proxy/custom_object.pb.h"
#include "mongo_proxy/mongo_service.grpc.pb.h"
#include "mongoc.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using mongo_service::BsonError;
using mongo_service::DbDetails;

class MongoServiceImpl final : public mongo_service::Mongo::Service {
  // Insert method
  Status Insert(ServerContext *context, const CustomObject *request,
                BsonError *reply) override {
    // Convert proto to json
    std::string json_string;
    google::protobuf::util::MessageToJsonString(*request, &json_string);
    // Convert json to bson
    bson_t *doc;
    bson_error_t error;
    doc = bson_new_from_json((const unsigned char *)json_string.c_str(), -1,
                             &error);
    assert(doc);
    mongoc_collection_insert(collection_, MONGOC_INSERT_NONE, doc, NULL,
                             &error);
    // Copy the error details
    reply->set_domain(error.domain);
    reply->set_code(error.code);
    reply->set_msg(error.message);
    bson_destroy(doc);
    return Status::OK;
  }

  Status Init(ServerContext *context, const DbDetails *request,
              BsonError *rpc_reply) override {
    // TODO: Implement destroy method
    mongoc_init();
    client_ = mongoc_client_new(request->server().c_str());
    assert(client_);
    mongoc_client_set_appname(client_, "mongo-grpc-proxy");
    database_ = mongoc_client_get_database(client_, request->db().c_str());
    assert(database_);
    collection_ = mongoc_client_get_collection(client_, request->db().c_str(),
                                               request->collection().c_str());
    assert(collection_);
    return Status::OK;
  }

private:
  mongoc_client_t *client_;
  mongoc_database_t *database_;
  mongoc_collection_t *collection_;
};

int main(int argc, char **argv) {
  std::string server_address("0.0.0.0:50050");
  MongoServiceImpl service;
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}
