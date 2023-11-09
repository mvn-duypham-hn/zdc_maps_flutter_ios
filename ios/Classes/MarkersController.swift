//
//  MarkerController.swift
//  zdc_maps_flutter_ios
//
//  Created by Duy Pham X. VN.Hanoi on 08/11/2023.
//

import Flutter
import UIKit
import ZDCMaps
import Foundation

class MarkersController: NSObject {
    private var _methodChannel: FlutterMethodChannel
    private var _mapView: ZMSMapView
    private var _registrar: FlutterPluginRegistrar
    private var _markerIdentifierToController: NSMutableDictionary
    
    
    init(methodChannel: FlutterMethodChannel, mapView: ZMSMapView, registrar: FlutterPluginRegistrar) {
        _methodChannel = methodChannel
        _mapView = mapView
        _registrar = registrar
        _markerIdentifierToController = NSMutableDictionary.init()
        
        super.init()
    }
    
    func addMarkers(_ markersToAdd: NSArray) {
        for markerToAdd in markersToAdd {
            if let marker = markerToAdd as? [String: AnyObject] {
                let position = getPosition(marker)
                let identifier = marker["markerId"] as? String ?? ""
                let controller = ZdcMapMarkerController(position: position, identifier: identifier, mapView: _mapView)
                controller.interpretMarkerOptions(marker, registrar: _registrar)
                _markerIdentifierToController[identifier] = controller
            }
        }
    }
    
    func changeMarkers(_ markersToChange: NSArray) {
        for markerToChange in markersToChange {
            if let marker = markerToChange as? [String: AnyObject] {
                let identifier = marker["markerId"] as? String ?? ""
                if let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController {
                    controller.interpretMarkerOptions(marker, registrar: _registrar)
                }
            }
        }
    }
    
    func removeMarkersWithIdentifiers(_ identifiers: NSArray) {
        for identifier in identifiers {
            if let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController {
                controller.removeMarker()
                _markerIdentifierToController.removeObject(forKey: identifier)
            }
        }
    }
    
    func didTapMarkerWithIdentifier(_ identifier: Any) -> Bool {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else { return false }
        _methodChannel.invokeMethod("marker#onTap", arguments: ["markerId": identifier])
        return controller.consumeTapEvents
    }
    
    func didStartDraggingMarkerWithIdentifier(_ identifier: Any, location: CLLocationCoordinate2D) {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else { return }
        _methodChannel.invokeMethod("marker#onDragStart", arguments: ["markerId": identifier, "position": ZdcMapJsonConversions.arrayFromLocation(location)])
    }
    
    func didDragMarkerWithIdentifier(_ identifier: Any, location: CLLocationCoordinate2D) {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else { return }
        _methodChannel.invokeMethod("marker#onDrag", arguments: ["markerId": identifier, "position": ZdcMapJsonConversions.arrayFromLocation(location)])
    }
    
    func didEndDraggingMarkerWithIdentifier(_ identifier: Any, location: CLLocationCoordinate2D) {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else { return }
        _methodChannel.invokeMethod("marker#onDragEnd", arguments: ["markerId": identifier, "position": ZdcMapJsonConversions.arrayFromLocation(location)])
    }
    
    func didTapInfoWindowOfMarkerWithIdentifier(_ identifier: Any) {
        if let _ = _markerIdentifierToController[identifier] {
            _methodChannel.invokeMethod("infoWindow#onTap", arguments: ["markerId": identifier])
        }
    }
    
    func showMarkerInfoWindowWithIdentifier(_ identifier: Any, result: FlutterResult) {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else {
            result(FlutterError(code: "Invalid markerId", message: "showInfoWindow called with invalid markerId", details: nil))
            return
        }
        
        controller.showInfoWindow()
        result(nil)
    }
    
    func hideMarkerInfoWindowWithIdentifier(_ identifier: Any, result: FlutterResult) {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else {
            result(FlutterError(code: "Invalid markerId", message: "hideInfoWindow called with invalid markerId", details: nil))
            return
        }
        
        controller.showInfoWindow()
        result(nil)
    }
    
    func isInfoWindowShownForMarkerWithIdentifier(_ identifier: Any, result: FlutterResult) {
        guard let controller = _markerIdentifierToController[identifier] as? ZdcMapMarkerController else {
            result(FlutterError(code: "Invalid markerId", message: "isInfoWindowShown called with invalid markerId", details: nil))
            return
        }
        
        result(controller.isInfoWindowShown())
    }
    
    func getPosition(_ marker: [String: Any]) -> CLLocationCoordinate2D {
        let position = marker["position"] as? Array<AnyObject>
        return ZdcMapJsonConversions.locationFromLatLong(position!)
    }
}
