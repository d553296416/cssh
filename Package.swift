// swift-tools-version:5.10

import PackageDescription

let package = Package(
    name: "CSSH",
    platforms: [
        .macOS(.v13),
        .iOS(.v16),
    ],
    products: [
        .library(
            name: "CSSH",
            targets: ["CSSH"]
        ),
        .library(
            name: "SSHKey",
            targets: ["SSHKey"]
        ),
        .library(
            name: "OpenSSL",
            targets: ["OpenSSL"]
        ),
    ],
    dependencies: [],
    targets: [
        .target(
            name: "SSHKey",
            dependencies: ["OpenSSL"]
        ),
        .target(
            name: "CSSH",
            dependencies: ["OpenSSL"],
            cSettings: [
                .unsafeFlags(["-w"]),
                .define("HAVE_LIBSSL"),
                .define("HAVE_LIBZ"),
                .define("LIBSSH2_HAVE_ZLIB"),
                .define("LIBSSH2_OPENSSL"),
                .define("LIBSSH2DEBUG"),
                .define("STDC_HEADERS"),
                .define("WORDS_BIGENDIAN"),
                // .define("HAVE_POLL"),
                .define("HAVE_SELECT"),
                .define("HAVE_ALLOCA"),
                .define("HAVE_ALLOCA_H"),
                .define("HAVE_ARPA_INET_H"),
                .define("HAVE_GETTIMEOFDAY"),
                .define("HAVE_INTTYPES_H"),
                .define("HAVE_MEMSET_S"),
                .define("HAVE_NETINET_IN_H"),
                .define("HAVE_O_NONBLOCK"),
                .define("HAVE_SNPRINTF"),
                .define("HAVE_STDIO_H"),
                .define("HAVE_STRTOLL"),
                .define("HAVE_SYS_IOCTL_H"),
                .define("HAVE_SYS_PARAM_H"),
                .define("HAVE_SYS_SELECT_H"),
                .define("HAVE_SYS_SOCKET_H"),
                .define("HAVE_SYS_TIME_H"),
                .define("HAVE_SYS_UIO_H"),
                .define("HAVE_SYS_UN_H"),
                .define("HAVE_UNISTD_H"),
            ],
            linkerSettings: [
                .linkedLibrary("z"),
            ]
        ),
        .binaryTarget(
            name: "OpenSSL",
            path: "xcframework/OpenSSL.xcframework"
        ),
    ]
)
