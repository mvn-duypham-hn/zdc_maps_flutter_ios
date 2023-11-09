//
//  ZMSCoordinateBounds.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

@class ZMSPath;

NS_ASSUME_NONNULL_BEGIN

/// ## 領域クラス
/// 北東と南西の座標を指定して、地図上の領域を表現する。
@interface ZMSCoordinateBounds : NSObject

// MARK: - プロパティー

/// ### 北東の座標 (読み取り専用)
@property(nonatomic, readonly) CLLocationCoordinate2D northEast;

/// ### 南西の座標 (読み取り専用)
@property(nonatomic, readonly) CLLocationCoordinate2D southWest;

/// ### 有効な領域かどうか (読み取り専用)
/// `northEast` か `southWest` に不正な座標が含まれている場合NOを返す。<br>例) `[ZMSCoordinateBounds new].valid == NO`
@property(nonatomic, readonly, getter=isValid) BOOL valid;

// MARK: - メソッド

/// ### 座標2点からZMSCoordinateBoundsを作成する
/// @param coord1: 座標1(緯度/経度)
/// @param coord2: 座標2(緯度/経度)
/// @return 領域
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coord1 coordinate:(CLLocationCoordinate2D)coord2;

@end

NS_ASSUME_NONNULL_END
