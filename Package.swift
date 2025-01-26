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
            name: "MaxMindDB",
            targets: ["MaxMindDB"]
        ),
    ],
    dependencies: [],
    targets: [
        .target(
            name: "SSHKey",
            dependencies: ["CSSH"],
            linkerSettings: [
                .linkedLibrary("z"),
            ]
        ),
        .target(
            name: "MaxMindDB"
        ),
//        .binaryTarget(
//            name: "wolfSSL",
//            path: "xcframework/wolfSSL.xcframework"
//        ),
        .binaryTarget(
            name: "CSSH",
            path: "xcframework/CSSH.xcframework"
        ),
    ]
)
