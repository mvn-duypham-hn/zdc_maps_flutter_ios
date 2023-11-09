#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint zdc_maps_flutter_ios.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'zdc_maps_flutter_ios'
  s.version          = '0.0.1'
  s.summary          = 'A new Flutter plugin project.'
  s.description      = <<-DESC
A new Flutter plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.dependency 'Flutter'
  s.platform = :ios, '11.0'
  s.resources = 'Assets/*.png'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  s.swift_version = '5.0'

  s.preserve_paths = 'ZDCMaps.framework/**/*'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-framework ZDCMaps' }
  s.vendored_frameworks = 'ZDCMaps.framework'
end
