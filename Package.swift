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
    ],
    targets: [
        .target(
            name: "CSSH",
            exclude: ["dns.h", "dns.c"],
            dependencies: ["CSSHOpenSSL"],
            path: "src",
            linkerSettings: [
                .linkedLibrary("z"),
            ]
        ),
        .binaryTarget(
            name: "CSSHOpenSSL",
            path: "xcframework/CSSH.xcframework"
        )
    ],
    swiftLanguageVersions: [.v5]
)
