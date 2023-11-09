import UIKit
import Flutter
import ZDCMaps

@UIApplicationMain
@objc class AppDelegate: FlutterAppDelegate {
    override func application(
        _ application: UIApplication,
        didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?
    ) -> Bool {
        
        let result = ZMSServices.provideConsumerKey("<YOUR_CONSUMER_KEY>", secretKey: "<YOUR_SECRET_KEY>", certificateDomain: "test.core.its-mo.com")
        GeneratedPluginRegistrant.register(with: self)
        return super.application(application, didFinishLaunchingWithOptions: launchOptions)
    }
}
