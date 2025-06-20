
Pod::Spec.new do |s|
  s.name             = 'CSSH'
  s.version          = '0.1.0'
  s.summary          = 'SSH,libssh2'
  s.description      = "libssh2 + OpenSSL"
  s.homepage         = 'https://github.com/sshterm/cssh'
  s.license          = 'MIT'
  s.author           = { 'sshterm' => 'admin@ssh2.app' }
  s.source           = { :git => 'https://github.com/sshterm/cssh.git', :tag => s.version.to_s }
  s.default_subspecs = :none
  s.ios.deployment_target = '16.0'
  s.osx.deployment_target = '13.0'
  s.subspec 'OpenSSL' do |cs|
    cs.source_files = ['src/**/*.{c,h}','Sources/**/*.{c,h}']
    cs.public_header_files = ['src/**/*.h','Sources/CSSH/include/**/*.h','Sources/SSHKey/include/**/*.h']
    cs.vendored_frameworks = ["xcframework/OpenSSL.xcframework"]
    cs.compiler_flags = '-DHAVE_LIBSSL=1','-DHAVE_LIBZ=1','-DLIBSSH2_HAVE_ZLIB=1','-DLIBSSH2_OPENSSL=1','-DSTDC_HEADERS=1','-DHAVE_ALLOCA=1','-DHAVE_ALLOCA_H=1','-DHAVE_ARPA_INET_H=1','-DHAVE_GETTIMEOFDAY=1','-DHAVE_INTTYPES_H=1','-DHAVE_MEMSET_S=1','-DHAVE_NETINET_IN_H=1','-DHAVE_O_NONBLOCK=1','-DHAVE_SELECT=1','-DHAVE_SNPRINTF=1','-DHAVE_STDIO_H=1','-DHAVE_STRTOLL=1','-DHAVE_SYS_IOCTL_H=1','-DHAVE_SYS_PARAM_H=1','-DHAVE_SYS_SELECT_H=1','-DHAVE_SYS_SOCKET_H=1','-DHAVE_SYS_TIME_H=1','-DHAVE_SYS_UIO_H=1','-DHAVE_SYS_UN_H=1','-DHAVE_UNISTD_H=1','-DLIBSSH2DEBUG=1'
    cs.libraries = 'z'
  end
  s.subspec 'OpenSSLFull' do |cs|
    cs.source_files = ['src/**/*.{c,h}','Sources/**/*.{c,h}']
    cs.public_header_files = ['src/**/*.h','Sources/CSSH/include/**/*.h','Sources/SSHKey/include/**/*.h']
    cs.dependency 'OpenSSL-Universal'
    cs.compiler_flags = '-DHAVE_LIBSSL=1','-DHAVE_LIBZ=1','-DLIBSSH2_HAVE_ZLIB=1','-DLIBSSH2_OPENSSL=1','-DSTDC_HEADERS=1','-DHAVE_ALLOCA=1','-DHAVE_ALLOCA_H=1','-DHAVE_ARPA_INET_H=1','-DHAVE_GETTIMEOFDAY=1','-DHAVE_INTTYPES_H=1','-DHAVE_MEMSET_S=1','-DHAVE_NETINET_IN_H=1','-DHAVE_O_NONBLOCK=1','-DHAVE_SELECT=1','-DHAVE_SNPRINTF=1','-DHAVE_STDIO_H=1','-DHAVE_STRTOLL=1','-DHAVE_SYS_IOCTL_H=1','-DHAVE_SYS_PARAM_H=1','-DHAVE_SYS_SELECT_H=1','-DHAVE_SYS_SOCKET_H=1','-DHAVE_SYS_TIME_H=1','-DHAVE_SYS_UIO_H=1','-DHAVE_SYS_UN_H=1','-DHAVE_UNISTD_H=1','-DLIBSSH2DEBUG=1'
    cs.libraries = 'z'
  end
end
