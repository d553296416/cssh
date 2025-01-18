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
        .binaryTarget(
            name: "CSSH",
            path: "xcframework/CSSH.xcframework"
        )
    ],
    swiftLanguageVersions: [.v5]
)
