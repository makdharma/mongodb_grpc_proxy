#include <string>

#include <grpc++/grpc++.h>

#include "mongo_proxy/custom_object.pb.h"
#include "mongo_proxy/mongo_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mongo_service::BsonError;
using mongo_service::DbDetails;
using mongo_service::Mongo;

class MongoGrpcClient {
public:
  MongoGrpcClient(std::shared_ptr<Channel> channel)
      : stub_(Mongo::NewStub(channel)) {}

  void Init() {
    DbDetails request;
    request.set_server("mongodb://localhost:27017");
    request.set_db("test");
    request.set_collection("coll");
    BsonError reply;
    ClientContext context;
    Status status = stub_->Init(&context, request, &reply);
    if (!status.ok()) {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
    }
  }

  void Insert() {
    std::unique_ptr<CustomObject> new_obj(new CustomObject);
    (*new_obj->mutable_attr())["blah"] = 1.0;
    BsonError reply;
    ClientContext context;
    Status status = stub_->Insert(&context, *new_obj, &reply);
    if (!status.ok()) {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
    }
    std::cout << "Return: " << reply.msg() << std::endl;
  }

private:
  std::unique_ptr<Mongo::Stub> stub_;
};

int main(int argc, char **argv) {
  MongoGrpcClient client(grpc::CreateChannel(
      "localhost:50050", grpc::InsecureChannelCredentials()));
  client.Init();
  client.Insert();
  return 0;
}
