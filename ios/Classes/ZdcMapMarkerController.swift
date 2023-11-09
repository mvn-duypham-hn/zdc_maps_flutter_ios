//
//  ZdcMapMarkerController.swift
//  zdc_maps_flutter_ios
//
//  Created by Duy Pham X. VN.Hanoi on 09/11/2023.
//

import Flutter
import UIKit
import ZDCMaps
import Foundation

class ZdcMapMarkerController: NSObject {
    private var _marker: ZMSMarker?
    private var _mapView: ZMSMapView
    var consumeTapEvents: Bool = false
    
    init(position: CLLocationCoordinate2D, identifier identifer: String, mapView: ZMSMapView) {
        
        _marker = ZMSMarker(position: position)
        _mapView = mapView
        _marker?.userData = identifer
        
        super.init()
    }
    
    func showInfoWindow() {
        _mapView.selectedMarker = _marker
    }
    
    func hideInfoWindow() {
        _mapView.selectedMarker = nil
    }
    
    func isInfoWindowShown()-> Bool {
        return _mapView.selectedMarker == _marker
    }
    
    func removeMarker() {
        _marker?.map = nil
    }
    
    func setAlpha(_ alpha: Float) {
        _marker?.opacity = alpha
    }
    
    func setAnchor(_ anchor: CGPoint) {
        _marker?.groundAnchor = anchor
    }
    
    func setDraggable(_ draggable: Bool) {}
    
    func setFlat(_ flat: Bool) {}
    
    func setIcon(_ icon: UIImage?) {
        _marker?.icon = icon
    }
    
    func setInfoWindowAnchor(_ anchor: CGPoint) {
        _marker?.infoWindowAnchor = anchor
    }
    
    func setInfoWindowTitle(_ title: String?, snippet: String?) {
        _marker?.title = title
        _marker?.snippet = snippet
    }
    
    func setPosition(_ position: CLLocationCoordinate2D) {
        _marker?.position = position
    }
    
    func setRotation(_ rotation: CLLocationDegrees) {
        _marker?.rotation = rotation
    }
    
    func setVisible(_ visible: Bool) {
        //        _marker?.isVisible = visible
        _marker?.map = visible ? _mapView : nil
    }
    
    func setZIndex(_ zIndex: Int) {
        _marker?.zIndex = zIndex
    }
    
    func interpretMarkerOptions(_ data: [String: AnyObject], registrar: FlutterPluginRegistrar) {
        if let alpha = data["alpha"] as? Float {
            setAlpha(alpha)
        }
        
        if let anchor = data["anchor"] as? Array<AnyObject> {
            setAnchor(ZdcMapJsonConversions.pointFromArray(anchor))
        }
        
        if let icon = data["icon"] as? NSArray {
            setIcon(extractIconFromData(icon, registrar: registrar))
        }
        
        if let flat = data["flat"]?.boolValue {
            setFlat(flat)
        }
        
        if let consumeTapEvents = data["consumeTapEvents"]?.boolValue {
            self.consumeTapEvents = consumeTapEvents
        }
        
        interpretInfoWindow(data)
        
        if let position = data["position"] as? Array<AnyObject> {
            setPosition(ZdcMapJsonConversions.locationFromLatLong(position))
        }
        
        if let rotation = data["rotation"]?.doubleValue {
            setRotation(rotation)
        }
        
        if let visible = data["visible"]?.boolValue {
            setVisible(visible)
        }
        
        if let zIndex = (data["zIndex"] as? NSNumber)?.intValue {
            setZIndex(zIndex)
        }
    }
    
    func extractIconFromData(_ iconData: NSArray, registrar: FlutterPluginRegistrar) -> UIImage? {
        let defaultImage: UIImage? = UIImage(named: "marker.png", in: Bundle(for: ZdcMapsFlutterPlugin.self), compatibleWith: nil)
        switch (iconData.firstObject as? String) {
        case "defaulMarker":
            return defaultImage
        case "fromAsset":
            if (iconData.count == 2) {
                return UIImage(named: registrar.lookupKey(forAsset: iconData[1] as! String))
            }
            return UIImage(named: registrar.lookupKey(forAsset: iconData[1] as! String, fromPackage: iconData[2] as! String))
        case "fromAssetImage":
            if (iconData.count == 3) {
                let img = UIImage(named: registrar.lookupKey(forAsset: iconData[1] as! String))
                let scaleParam = iconData[2]
                return scaleImage(img, by: scaleParam)
            }
            return nil
        case "fromBytes":
            if (iconData.count == 2) {
                let screenScale = UIScreen.main.scale
                if let byteData = iconData[1] as? FlutterStandardTypedData {
                    return UIImage(data: byteData.data, scale: screenScale)
                }
            }
            return nil
        default:
            return nil
        }
    }
    
    func scaleImage(_ image: UIImage?, by scaleParam: Any?) -> UIImage? {
        var scale = 1.0
        if (scaleParam is NSNumber) {
            scale = (scaleParam as? NSNumber)?.doubleValue ?? 0.0
        }
        
        if abs(Float(scale - 1)) > 1e-3 {
            if let cgImage = image?.cgImage, let imageOrientation = image?.imageOrientation {
                return UIImage(
                    cgImage: cgImage,
                    scale: (image?.scale ?? 0.0) * scale,
                    orientation: imageOrientation)
            }
            return nil
        }
        
        return nil
    }
    
    func interpretInfoWindow(_ data: [String: AnyObject]) {
        if let infoWindow = data["infoWindow"] as? [String: AnyObject] {
            let title = infoWindow["title"] as? String
            let snippet = infoWindow["snippet"] as? String
            setInfoWindowTitle(title, snippet: snippet)
        }
        
        if let infoWindowAnchor = data["infoWindowAnchor"] as? Array<AnyObject> {
            setInfoWindowAnchor(ZdcMapJsonConversions.pointFromArray(infoWindowAnchor))
        }
    }
}
