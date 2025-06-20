# cssh
libssh2 + OpenSSL + wolfSS

OpenSSL 支持公钥转OpenSSH格式


SSH Term APP [ssh2.app](https://ssh2.app/) 的 SSH2连接核心

# Swift Package Manager
```swift
.package(url: "https://github.com/sshterm/cssh.git", branch: "main"),
```
```swift
.product(name: "CSSH", package: "CSSH")
.product(name: "SSHKey", package: "CSSH")
.product(name: "OpenSSL", package: "CSSH")
```


# 使用 OpenSSL 版
```
pod 'CSSH/OpenSSL', :git => 'https://github.com/sshterm/cssh.git'
```
使用完整的OpenSSL包括libssl
```
pod 'CSSH/OpenSSLFull', :git => 'https://github.com/sshterm/cssh.git'
```

# 关于libssh2

https://github.com/libssh2/libssh2

# 关于OpenSSL

https://github.com/openssl/openssl