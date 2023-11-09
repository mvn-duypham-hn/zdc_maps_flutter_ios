//
//  ZMSProjection.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@class ZMSMapView;

NS_ASSUME_NONNULL_BEGIN

// ## マップの表示領域
// @note 通常は長方形となるが、カメラが傾いているときは台形となる。
/// :nodoc:
typedef struct {
    // 画面の左下の座標
    CLLocationCoordinate2D nearLeft;
    // 画面の右下の座標
    CLLocationCoordinate2D nearRight;
    // 画面の左上の座標
    CLLocationCoordinate2D farLeft;
    // 画面の右上の座標
    CLLocationCoordinate2D farRight;
} ZMSVisibleRegion;

/// ## 座標(緯度/経度)とスクリーン座標(X/Y)情報クラス
/// 地図上の座標(緯度/経度)とスクリーン上の座標(X/Y)の情報を取得する。<br>`ZMSMapView.projection`経由で利用する。
/// @note 初期化不可
@interface ZMSProjection : NSObject

// MARK: - メソッド

/// ### 座標をスクリーン座標に変換する
/// @param coordinate: 座標(緯度/経度)
/// @return スクリーン座標(X/Y)
- (CGPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;

/// ### スクリーン座標を座標に変換する
/// @param point: スクリーン座標(X/Y)
/// @return 座標(緯度/経度)
- (CLLocationCoordinate2D)coordinateForPoints:(CGPoint)point;

/// :nodoc:
- (instancetype)init __attribute__((unavailable("init is not available")));

@end

NS_ASSUME_NONNULL_END
