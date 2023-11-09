//
//  ZdcMapJsonConversions.swift
//  zdc_maps_flutter_ios
//
//  Created by Duy Pham X. VN.Hanoi on 08/11/2023.
//

import Flutter
import ZDCMaps

class ZdcMapJsonConversions {
    static func locationFromLatLong(_ latlong: Array<AnyObject>) -> CLLocationCoordinate2D {
        return CLLocationCoordinate2DMake(latlong[0].doubleValue, latlong[1].doubleValue)
    }
    
    static func pointFromArray(_ array: Array<AnyObject>)-> CGPoint {
        return CGPointMake(array[0].doubleValue, array[1].doubleValue)
    }
    
    static func arrayFromLocation(_ location: CLLocationCoordinate2D) -> Array<CLLocationDegrees> {
        return [location.latitude, location.longitude]
    }
    
    static func colorFromRGBA(_ numberColor: UInt) -> UIColor {
        return UIColor(
            red: CGFloat((numberColor & 0xFF0000) >> 16) / 255.0,
            green: CGFloat((numberColor & 0x00FF00) >> 8) / 255.0,
            blue: CGFloat(numberColor & 0x0000FF) / 255.0,
            alpha: CGFloat(1.0)
        )
    }
    
    static func pointFromLatLongs(_ data: Array<Array<AnyObject>>) -> Array<CLLocation>{
        var points = Array<CLLocation>.init()
        for i in 0..<data.count {
            let lat = data[i][0]
            let lng = data[i][1]
            let point = CLLocation(latitude: lat.doubleValue, longitude: lng.doubleValue)
            points.append(point)
        }
        
        return points
    }
    
    static func cameraPostionFromDictionary(_ data: [String: Any]?) -> ZMSCameraPosition? {
        guard let dict = data else { return nil }
        let target = ZdcMapJsonConversions.locationFromLatLong(dict["target"] as! Array<AnyObject>)
        let zoom = (dict["zoom"] as AnyObject).floatValue ?? 14
        let bearing = (dict["bearing"] as AnyObject).doubleValue ?? 0
        let titl = (dict["titl"] as AnyObject).doubleValue ?? 0
        
        return ZMSCameraPosition(target: target, zoom: zoom, bearing: bearing, viewingAngle: titl)
    }
    
    static func dictionaryFromPosition(_ postion: ZMSCameraPosition?) -> [String: Any]? {
        guard let pos = postion else { return nil }
        return [
            "target": arrayFromLocation(pos.target),
            "zoom": pos.zoom,
            "bearing": pos.bearing,
            "tilt": pos.viewingAngle
        ]
    }
    
    static func dictionaryFromPoint(_ point: CGPoint) ->  [String: Any] {
        return [
            "x": lroundf(Float(point.x)),
            "y": lroundf(Float(point.y))
        ]
    }
    
    static func pointFromDictionary(_ dictionary: [String: AnyObject]) -> CGPoint {
        let x = dictionary["x"]?.doubleValue
        let y = dictionary["y"]?.doubleValue
        return CGPointMake(x!, y!)
    }
    
    static func cameraUpdateFromChannelValue(_ channelValue: NSArray) -> ZMSCameraUpdate? {
        guard let update = channelValue[0] as? String else { return nil }
        switch (update) {
        case "newCameraPosition":
            return ZMSCameraUpdate.setCamera(cameraPostionFromDictionary(channelValue[1] as? [String : Any]))
        case "newLatLng":
            return ZMSCameraUpdate.setTarget(locationFromLatLong(channelValue[1] as! Array<AnyObject>))
        case "newLatLngBounds":
            return ZMSCameraUpdate.fit(coordinateBoundsFromLatLongs(channelValue[1] as! NSArray), withPadding: (channelValue[2] as AnyObject).doubleValue)
        case "newLatLngZoom":
            return ZMSCameraUpdate.setTarget(locationFromLatLong(channelValue[1] as! Array<AnyObject>), zoom: channelValue[2] as! Float)
        case "scrollBy":
            return ZMSCameraUpdate.scrollBy(x: (channelValue[1] as AnyObject).doubleValue, y: (channelValue[2] as AnyObject).doubleValue)
        case "zoomBy":
            if channelValue.count == 2 {
                return ZMSCameraUpdate.zoom(by: (channelValue[1] as AnyObject).floatValue)
            }
            return ZMSCameraUpdate.zoom(by: (channelValue[1] as AnyObject).floatValue, at: pointFromArray(channelValue[2] as! Array<AnyObject>))
        case "zoomIn":
            return ZMSCameraUpdate.zoomIn()
        case "zoomOut":
            return ZMSCameraUpdate.zoomOut()
        case "zoomTo":
            return ZMSCameraUpdate.zoom(to: (channelValue[1] as AnyObject).floatValue)
        default:
            return nil
        }
    }
    
    static func coordinateBoundsFromLatLongs(_ latLngs: NSArray) -> ZMSCoordinateBounds {
        return ZMSCoordinateBounds(coordinate: locationFromLatLong(latLngs[0] as! Array<AnyObject>), coordinate: locationFromLatLong(latLngs[1] as! Array<AnyObject>))
    }
}
