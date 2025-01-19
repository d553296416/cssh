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
            linkerSettings: [
                .linkedLibrary("z"),
            ]
        ),
        .binaryTarget(
            name: "OpenSSL",
            path: "xcframework/CSSH.xcframework"
        )
    ]
)
