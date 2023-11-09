// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:flutter/material.dart';
import 'package:zdc_maps_flutter_ios_example/padding.dart';
import 'package:zdc_maps_flutter_ios_example/place_circle.dart';
import 'package:zdc_maps_flutter_ios_example/place_marker.dart';
import 'package:zdc_maps_flutter_ios_example/place_polygon.dart';
import 'package:zdc_maps_flutter_ios_example/place_polyline.dart';
import 'package:zdc_maps_flutter_ios_example/scrolling_map.dart';
import 'package:zdc_maps_flutter_ios_example/snapshot.dart';
import 'package:zdc_maps_flutter_ios_example/tile_overlay.dart';

import 'animate_camera.dart';
import 'lite_mode.dart';
import 'map_click.dart';
import 'map_coordinates.dart';
import 'map_map_id.dart';
import 'map_ui.dart';
import 'maps_demo.dart';
import 'marker_icons.dart';
import 'move_camera.dart';
import 'page.dart';

void main() {
  runApp(const MaterialApp(
      home: MapsDemo(<GoogleMapExampleAppPage>[
    MapUiPage(),
    MapCoordinatesPage(),
    MapClickPage(),
    AnimateCameraPage(),
    MoveCameraPage(),
    PlaceMarkerPage(),
    MarkerIconsPage(),
    ScrollingMapPage(),
    PlacePolylinePage(),
    PlacePolygonPage(),
    PlaceCirclePage(),
    PaddingPage(),
    SnapshotPage(),
    LiteModePage(),
    TileOverlayPage(),
    MapIdPage(),
  ])));
}
