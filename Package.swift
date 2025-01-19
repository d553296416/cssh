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
            dependencies: ["CSSH"],
            path: "src",
            exclude: ["dns.h", "dns.c"],
            linkerSettings: [
                .linkedLibrary("z"),
            ]
        ),
        .binaryTarget(
            name: "CSSH",
            path: "xcframework/CSSH.xcframework"
        )
    ]
)
