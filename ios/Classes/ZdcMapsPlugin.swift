//
//  ZdcMapsPlugin.swift
//  zdc_maps_flutter_ios
//
//  Created by Duy Pham X. VN.Hanoi on 08/11/2023.
//

import Flutter
import UIKit

public class ZdcMapsFlutterPlugin: NSObject, FlutterPlugin {
    public static func register(with registrar: FlutterPluginRegistrar) {
        let zdcMapViewFactory = ZDCMapViewFactory(registrar: registrar)
        registrar.register(zdcMapViewFactory, withId: "vn.duypx/zdc_maps_ios", gestureRecognizersBlockingPolicy: FlutterPlatformViewGestureRecognizersBlockingPolicyWaitUntilTouchesEnded)
    }
}
