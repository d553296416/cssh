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
        .library(
            name: "MaxMindDB",
            targets: ["MaxMindDB"]
        ),
    ],
    dependencies: [],
    targets: [
        .target(
            name: "SSHKey",
            dependencies: ["OpenSSL"]
        ),
        .target(
            name: "MaxMindDB",
            cSettings: [
                .unsafeFlags(["-w"]),
                .define("HAVE_ARPA_INET_H"),
                .define("HAVE_ASSERT_H"),
                .define("HAVE_CLOCK_GETTIME"),
                .define("HAVE_DLFCN_H"),
                .define("HAVE_FCNTL_H"),
                .define("HAVE_GETPAGESIZE"),
                .define("HAVE_INTTYPES_H"),
                .define("HAVE_LIBGEN_H"),
                .define("HAVE_MATH_H"),
                .define("HAVE_MMAP"),
                .define("HAVE_NETDB_H"),
                .define("HAVE_NETINET_IN_H"),
                .define("HAVE_OPEN_MEMSTREAM"),
                .define("HAVE_STDARG_H"),
                .define("HAVE_STDBOOL_H"),
                .define("HAVE_STDINT_H"),
                .define("HAVE_STDIO_H"),
                .define("HAVE_STDLIB_H"),
                .define("HAVE_STRINGS_H"),
                .define("HAVE_STRING_H"),
                .define("HAVE_SYS_MMAN_H"),
                .define("HAVE_SYS_PARAM_H"),
                .define("HAVE_SYS_SOCKET_H"),
                .define("HAVE_SYS_STAT_H"),
                .define("HAVE_SYS_TIME_H"),
                .define("HAVE_SYS_TYPES_H"),
                .define("HAVE_UNISTD_H"),
            ]
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
                .define("HAVE_POLL"),
                // .define("HAVE_SELECT"),
                // .define("HAVE_SYS_SELECT_H"),
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
