//
//  ZdcMapController.swift
//  zdc_maps_flutter_ios
//
//  Created by Duy Pham X. VN.Hanoi on 08/11/2023.
//

import Flutter
import UIKit
import ZDCMaps
import Foundation

class ZdcMapController: NSObject, FlutterPlatformView, ZMSMapViewDelegate {
    private var _mapView: ZMSMapView
    private var _registrar: FlutterPluginRegistrar
    private var _channel: FlutterMethodChannel
    
    private var _markersController: MarkersController
    private var _trackCameraPosition: Bool = false
    
    func view() -> UIView {
        return _mapView
    }
    
    init(frame: CGRect,
         viewIdentifier viewId: Int64,
         arguments args: Any?,
         registrar: FlutterPluginRegistrar
    ) {
        //        let camera = ZMSCameraPosition.camera(withLatitude: 35.6276017, longitude: 139.7409166, zoom: 13)
        //        _mapView = ZMSMapView.map(withFrame: frame, camera: camera)
        //        _mapView.accessibilityElementsHidden = false
        //        _registrar = registrar
        //
        //        let channelName = "vn.duypx/zdc_maps_\(viewId)"
        //        _channel = FlutterMethodChannel(name: channelName, binaryMessenger: registrar.messenger())
        //
        //        super.init()
        //
        //        _mapView.delegate = self
        //        _mapView.mapType = _mapView.mapTypeList[1]
        //
        //        _mapView.addObserver(self, forKeyPath: "frame", options: [], context: nil)
        
        let channelName = "vn.duypx/zdc_maps_ios_\(viewId)"
        _channel = FlutterMethodChannel(name: channelName, binaryMessenger: registrar.messenger())
        
        let data = args as? [String: Any]
        let camera = ZdcMapJsonConversions.cameraPostionFromDictionary(data?["initialCameraPosition"] as? [String: Any])
        
        _mapView = ZMSMapView.map(withFrame: frame, camera: camera)
        _mapView.accessibilityElementsHidden = false
        _mapView.mapType = _mapView.mapTypeList[1]
        
        _registrar = registrar
        
        _markersController = MarkersController(methodChannel: _channel, mapView: _mapView, registrar: registrar)
        
        super.init()
        
        _channel.setMethodCallHandler(onMethodCall)
        
        _mapView.delegate = self
        
        if let options = data?["options"] as? [String: Any] {
            interpretMapOptions(options)
        }
        
        if let markersToAdd = data?["markersToAdd"] as? NSArray {
            _markersController.addMarkers(markersToAdd)
        }
        
        _mapView.addObserver(self, forKeyPath: "frame", options: [], context: nil)
    }
    
    func interpretMapOptions(_ options: [String: Any]) {
        //        let cloudMapId = options["cloudMapId"]
        //        if (cloudMapId != nil) {
        //        }
        if let cameraTargetBounds = options["cameraTargetBounds"] as? NSArray {
            if let bounds = cameraTargetBounds[0] as? NSArray {
                setCameraTargetBounds(ZdcMapJsonConversions.coordinateBoundsFromLatLongs(bounds))
            }
        }
        
        if let compassEnabled = options["compassEnabled"] as? Bool {
            setCompassEnabled(compassEnabled)
        }
        
        if let indoorEnabled = options["indoorEnabled"] as? Bool {
            setIndoorEnabled(indoorEnabled)
        }
        
        if let mapType = options["mapType"] as? Int {
            setMapType(mapType)
        }
        
        if let zoomData = options["minMaxZoomPreference"] as? NSArray,
           let minZoom = zoomData[0] as? Float,
           let maxZoom = zoomData[1] as? Float {
            setMinZoom(minZoom, maxZoom: maxZoom)
        }
        
        if let padding = options["padding"] as? NSArray,
           let top = padding[0] as? CGFloat,
           let left = padding[1] as? CGFloat,
           let bottom = padding[2] as? CGFloat,
           let right = padding[3] as? CGFloat {
            setPadding(top: top, left: left, bottom: bottom, right: right)
        }
        
        if let rotateGesturesEnabled = options["rotateGesturesEnabled"] as? Bool {
            setRotateGesturesEnabled(rotateGesturesEnabled)
        }
        
        if let scrollGesturesEnabled = options["scrollGesturesEnabled"] as? Bool {
            setScrollGesturesEnabled(scrollGesturesEnabled)
        }
        
        if let tiltGesturesEnabled = options["tiltGesturesEnabled"] as? Bool {
            setTiltGesturesEnabled(tiltGesturesEnabled)
        }
        
        if let zoomGesturesEnabled = options["zoomGesturesEnabled"] as? Bool {
            setZoomGesturesEnabled(zoomGesturesEnabled)
        }
        
        if let myLocationEnabled = options["myLocationEnabled"] as? Bool {
            setMyLocationEnabled(myLocationEnabled)
        }
        
        if let myLocationButtonEnabled = options["myLocationButtonEnabled"] as? Bool {
            setMyLocationButtonEnabled(myLocationButtonEnabled)
        }
        
        if let trackCameraPosition = options["trackCameraPosition"] as? Bool {
            setTrackCameraPosition(trackCameraPosition)
        }
        
    }
    
    func cameraPosition() -> ZMSCameraPosition? {
        if (_trackCameraPosition) {
            return _mapView.camera
        }
        return nil
    }
    
    func setCameraTargetBounds(_ bounds: ZMSCoordinateBounds) {
        //        _mapView.
    }
    func setCompassEnabled(_ enabled: Bool) {
        _mapView.settings.compassButton = enabled
    }
    
    func setIndoorEnabled(_ enabled: Bool) {
        _mapView.settings.indoorEnabled = enabled
    }
    
    func setMapType(_ typeValue: Int) {
        _mapView.mapType = _mapView.mapTypeList[typeValue]
    }
    
    func setMinZoom(_ minZoom: Float, maxZoom: Float) {
        _mapView.setMinZoom(minZoom, maxZoom: maxZoom)
    }
    
    func setPadding(top: CGFloat, left: CGFloat, bottom: CGFloat, right: CGFloat) {
        _mapView.padding = UIEdgeInsets(top: top, left: left, bottom: bottom, right: right)
    }
    
    func setRotateGesturesEnabled(_ enabled: Bool) {
        _mapView.settings.rotateGestures = enabled;
    }
    
    func setScrollGesturesEnabled(_ enabled: Bool) {
        _mapView.settings.scrollGestures = enabled;
    }
    
    func setTiltGesturesEnabled(_ enabled: Bool) {
        _mapView.settings.tiltGestures = enabled;
    }
    
    func setZoomGesturesEnabled(_ enabled: Bool) {
        _mapView.settings.zoomGestures = enabled;
    }
    
    func setMyLocationEnabled(_ enabled: Bool) {
        _mapView.isMyLocationEnabled = enabled
    }
    
    func setMyLocationButtonEnabled(_ enabled: Bool) {
        _mapView.settings.myLocationButton = enabled;
    }
    
    func setTrackCameraPosition(_ enabled: Bool) {
        _trackCameraPosition = enabled
    }
    
    func onMethodCall(_ call: FlutterMethodCall, result: FlutterResult) {
        switch call.method {
        case "map#show":
            if let data = call.arguments as? [String: AnyObject], let x = data["x"], let y = data["y"] {
                let origin = CGPointMake(x.doubleValue, y.doubleValue)
                showAtOrigin(origin)
            }
            result(nil)
        case "map#hide":
            hide()
            result(nil)
        case "map#update":
            if let data = call.arguments as? [String: AnyObject], let options = data["options"] as? [String: Any] {
                interpretMapOptions(options)
            }
            result(ZdcMapJsonConversions.dictionaryFromPosition(cameraPosition()))
        case "map#getScreenCoordinate":
            let location = ZdcMapJsonConversions.locationFromLatLong(call.arguments as! Array<AnyObject>)
            let point = _mapView.projection.point(for: location)
            result(ZdcMapJsonConversions.dictionaryFromPoint(point))
        case "map#getLatLng":
            let point = ZdcMapJsonConversions.pointFromDictionary(call.arguments as! [String: AnyObject])
            let latLng = _mapView.projection.coordinate(forPoints: point)
            result(ZdcMapJsonConversions.arrayFromLocation(latLng))
        case "map#waitForMap":
            result(nil)
        case "map#takeSnapshot":
            result(nil)
        case "map#isCompassEnabled":
            result(_mapView.settings.compassButton)
        case "map#isMapToolbarEnabled":
            result(false)
        case "map#getMinMaxZoomLevels":
            result([_mapView.minZoom, _mapView.maxZoom])
        case "map#getZoomLevel":
            result(_mapView.camera.zoom)
        case "map#isZoomGesturesEnabled":
            result(_mapView.settings.zoomGestures)
        case "map#isZoomControlsEnabled":
            result(false)
        case "map#isTiltGesturesEnabled":
            result(_mapView.settings.tiltGestures)
        case "map#isRotateGesturesEnabled":
            result(_mapView.settings.rotateGestures)
        case "map#isScrollGesturesEnabled":
            result(_mapView.settings.scrollGestures)
        case "map#isMyLocationButtonEnabled":
            result(_mapView.settings.myLocationButton)
        case "map#isTrafficEnabled":
            result(false)
        case "map#isBuildingsEnabled":
            result(false)
        case "map#getTileOverlayInfo":
            result(nil)
        case "map#setStyle":
            setMapType(1)
            result(nil)
        case "camera#animate":
            if let data = call.arguments as? [String: AnyObject] {
                animateWithCameraUpdate(ZdcMapJsonConversions.cameraUpdateFromChannelValue(data["cameraUpdate"] as! NSArray)!)
            }
            result(nil)
        case "camera#move":
            if let data = call.arguments as? [String: AnyObject] {
                moveWithCameraUpdate(ZdcMapJsonConversions.cameraUpdateFromChannelValue(data["cameraUpdate"] as! NSArray)!)
            }
            result(nil)
        case "markers#update":
            if let data = call.arguments as? [String: AnyObject] {
                if let markersToAdd = data["markersToAdd"] as? NSArray {
                    _markersController.addMarkers(markersToAdd)
                }
                if let markersToChange = data["markersToChange"] as? NSArray {
                    _markersController.changeMarkers(markersToChange)
                }
                if let markerIdsToRemove = data["markerIdsToRemove"] as? NSArray {
                    _markersController.removeMarkersWithIdentifiers(markerIdsToRemove)
                }
            }
            result(nil)
        case "markers#showInfoWindow":
            guard let data = call.arguments as? [String: AnyObject], let markerId = data["markerId"] else {
                result(FlutterError(code: "Invalid markerId", message: "showInfoWindow called with invalid markerId", details: nil))
                return
            }
            
            _markersController.showMarkerInfoWindowWithIdentifier(markerId, result: result)
        case "markers#hideInfoWindow":
            guard let data = call.arguments as? [String: AnyObject], let markerId = data["markerId"] else {
                result(FlutterError(code: "Invalid markerId", message: "hideInfoWindow called with invalid markerId", details: nil))
                return
            }
            
            _markersController.hideMarkerInfoWindowWithIdentifier(markerId, result: result)
        case "markers#isInfoWindowShown":
            guard let data = call.arguments as? [String: AnyObject], let markerId = data["markerId"] else {
                result(FlutterError(code: "Invalid markerId", message: "isInfoWindowShown called with invalid markerId", details: nil))
                return
            }
            
            _markersController.isInfoWindowShownForMarkerWithIdentifier(markerId, result: result)
        case "tileOverlays#update":
            result(nil)
        case "tileOverlays#clearTileCache":
            result(nil)
        case "circles#update":
            result(nil)
        case "polygons#update":
            result(nil)
        case "polylines#update":
            result(nil)
        default:
            result(FlutterMethodNotImplemented)
        }
    }
    
    func showAtOrigin(_ origin: CGPoint) {
        let frame = CGRect(origin: origin, size: _mapView.frame.size)
        _mapView.frame = frame
        _mapView.isHidden = false
    }
    
    func hide() {
        _mapView.isHidden = true
    }
    
    func animateWithCameraUpdate(_ cameraUpdate: ZMSCameraUpdate) {
        _mapView.animate(with: cameraUpdate, duration: 0.5)
    }
    
    func moveWithCameraUpdate(_ cameraUpdate: ZMSCameraUpdate) {
        _mapView.moveCamera(cameraUpdate)
    }
    
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        if (object as! NSObject == self._mapView && keyPath == "frame") {
            let bounds = self._mapView.bounds
            if (bounds.equalTo(CGRect.zero)) {
                return
            }
            self._mapView.removeObserver(self, forKeyPath: "frame")
        } else {
            super.observeValue(forKeyPath: keyPath, of: object, change: change, context: context)
        }
        
    }

    func mapView(_ mapView: ZMSMapView, willMove gesture: Bool) {
        self._channel.invokeMethod("camera#onMoveStarted", arguments: ["isGesture": gesture])
    }
    
    func mapView(_ mapView: ZMSMapView, didChange position: ZMSCameraPosition) {
        self._channel.invokeMethod("camera#onMove", arguments: ["position": ZdcMapJsonConversions.dictionaryFromPosition(position)])
    }

    func mapView(_ mapView: ZMSMapView, didTap marker: ZMSMarker) -> Bool {
        return _markersController.didTapMarkerWithIdentifier(marker.userData)
    }
    
    func mapView(_ mapView: ZMSMapView, idleAt position: ZMSCameraPosition) {
        self._channel.invokeMethod("camera#onIdle", arguments: [])
    }
}
