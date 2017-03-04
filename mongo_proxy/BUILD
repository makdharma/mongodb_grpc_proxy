package(default_visibility = ["//visibility:public"])

load("//bazel:grpc_build_system.bzl", "grpc_proto_library")

grpc_proto_library(
    name = "mongo_service",
    srcs = [ "mongo_service.proto", ],
    deps = [ "//mongo_proxy:custom_object", ],
)

grpc_proto_library(
    name = "custom_object",
    srcs = [ "custom_object.proto", ],
)

libmongoc_inc = [
      "@bson_inc//:bson.h",
      "@bson_inc//:bson-compat.h",
      "@bson_inc//:bson-config.h",
      "@bson_inc//:bson-macros.h",
      "@bson_inc//:bson-stdint.h",
      "@bson_inc//:bson-atomic.h",
      "@bson_inc//:bson-context.h",
      "@bson_inc//:bson-types.h",
      "@bson_inc//:bson-endian.h",
      "@bson_inc//:bson-clock.h",
      "@bson_inc//:bson-decimal128.h",
      "@bson_inc//:bson-error.h",
      "@bson_inc//:bson-iter.h",
      "@bson_inc//:bson-json.h",
      "@bson_inc//:bson-keys.h",
      "@bson_inc//:bson-md5.h",
      "@bson_inc//:bson-memory.h",
      "@bson_inc//:bson-oid.h",
      "@bson_inc//:bson-reader.h",
      "@bson_inc//:bson-string.h",
      "@bson_inc//:bson-utf8.h",
      "@bson_inc//:bson-value.h",
      "@bson_inc//:bson-version.h",
      "@bson_inc//:bson-version-functions.h",
      "@bson_inc//:bson-writer.h",
      "@bson_inc//:bcon.h",
      "@mongoc_inc//:mongoc-apm.h",
      "@mongoc_inc//:mongoc-bulk-operation.h",
      "@mongoc_inc//:mongoc-client-pool.h",
      "@mongoc_inc//:mongoc-client.h",
      "@mongoc_inc//:mongoc-collection.h",
      "@mongoc_inc//:mongoc-config.h",
      "@mongoc_inc//:mongoc-cursor.h",
      "@mongoc_inc//:mongoc-database.h",
      "@mongoc_inc//:mongoc-error.h",
      "@mongoc_inc//:mongoc-find-and-modify.h",
      "@mongoc_inc//:mongoc-flags.h",
      "@mongoc_inc//:mongoc-gridfs-file-list.h",
      "@mongoc_inc//:mongoc-gridfs-file-page.h",
      "@mongoc_inc//:mongoc-gridfs-file.h",
      "@mongoc_inc//:mongoc-gridfs.h",
      "@mongoc_inc//:mongoc-handshake.h",
      "@mongoc_inc//:mongoc-host-list.h",
      "@mongoc_inc//:mongoc-index.h",
      "@mongoc_inc//:mongoc-init.h",
      "@mongoc_inc//:mongoc-iovec.h",
      "@mongoc_inc//:mongoc-log.h",
      "@mongoc_inc//:mongoc-matcher.h",
      "@mongoc_inc//:mongoc-opcode.h",
      "@mongoc_inc//:mongoc-rand.h",
      "@mongoc_inc//:mongoc-read-concern.h",
      "@mongoc_inc//:mongoc-read-prefs.h",
      "@mongoc_inc//:mongoc-server-description.h",
      "@mongoc_inc//:mongoc-socket.h",
      "@mongoc_inc//:mongoc-ssl.h",
      "@mongoc_inc//:mongoc-stream-buffered.h",
      "@mongoc_inc//:mongoc-stream-file.h",
      "@mongoc_inc//:mongoc-stream-gridfs.h",
      "@mongoc_inc//:mongoc-stream-socket.h",
      "@mongoc_inc//:mongoc-stream-tls-libressl.h",
      "@mongoc_inc//:mongoc-stream-tls-openssl.h",
      "@mongoc_inc//:mongoc-stream-tls-secure-channel.h",
      "@mongoc_inc//:mongoc-stream-tls-secure-transport.h",
      "@mongoc_inc//:mongoc-stream-tls.h",
      "@mongoc_inc//:mongoc-stream.h",
      "@mongoc_inc//:mongoc-topology-description.h",
      "@mongoc_inc//:mongoc-uri.h",
      "@mongoc_inc//:mongoc-version-functions.h",
      "@mongoc_inc//:mongoc-version.h",
      "@mongoc_inc//:mongoc-write-concern.h",
      "@mongoc_inc//:mongoc.h",
      "@mongoc_inc//:utlist.h",
]

cc_binary (
    name = "mongo_proxy_server",
    srcs = [
        "mongo_proxy_server.cc",
			  "@mongoc_lib//:libmongoc-1.0.dylib",
			  "@mongoc_lib//:libbson-1.0.dylib",
    ] + libmongoc_inc,
    deps = [
        ":mongo_service",
    ],
    copts = [
        "-Iexternal/bson_inc",
        "-Iexternal/mongoc_inc",
    ],
		linkopts = [
		    "-lmongoc-1.0",
			  "-lbson-1.0",
			  "-lsasl2",
		],
)

cc_binary (
    name = "mongo_proxy_client",
    srcs = [
      "mongo_proxy_client.cc",
    ],
    deps = [
        ":mongo_service",
    ],
)
