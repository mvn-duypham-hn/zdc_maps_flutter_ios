//
//  ZMSCameraPosition.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

/// ## カメラ位置情報クラス
/// カメラの位置情報を保持する。
/// @note 初期化不可。<br>イニシャライザーに有効範囲外の数値が設定された場合、有効範囲内に正規化される。
@interface ZMSCameraPosition : NSObject<NSCopying>

// MARK: - プロパティー

/// ### 座標 (読み取り専用)
/// カメラ位置の緯度/経度を指定する。
/// @note 緯度 / 経度
@property(nonatomic, readonly) CLLocationCoordinate2D target;

/// ### ズームレベル (読み取り専用)
/// 地図の縮尺を変更する。
/// @note 有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
@property(nonatomic, readonly) float zoom;

/// ### 方位角 (読み取り専用)
/// 地図の北を指定した角度に回転させる。
/// @note 有効範囲: 0 - 360度 (時計回り)<br>デフォルト値: 0<br>有効範囲を超えた分は循環し、360度以内に正規化される。
@property(nonatomic, readonly) CLLocationDirection bearing;

/// ### 傾き角度 (読み取り専用)
/// 地図の平面を指定した角度に傾ける。
/// @note 有効範囲: 0 - 30度 (0度は地図平面に対して直角)<br>デフォルト値: 0<br>超えた分は有効範囲内に正規化される。
@property(nonatomic, readonly) double viewingAngle;

// MARK: - メソッド

/// ### ZMSCameraPositionのイニシャライザー
/// @param target: 座標(緯度/経度)
/// @param zoom: ズームレベル
/// @param bearing: 方位角
/// @param viewingAngle: 傾き角度
- (instancetype)initWithTarget:(CLLocationCoordinate2D)target zoom:(float)zoom bearing:(CLLocationDirection)bearing viewingAngle:(double)viewingAngle;

/// ### 座標とズームレベルでZMSCameraPostionを生成する
/// @note `bearing` `viewingAngle`はデフォルト値(0)が設定される。
/// @param target: 座標(緯度/経度)
/// @param zoom: ズームレベル
/// @return カメラ位置情報
+ (instancetype)cameraWithTarget:(CLLocationCoordinate2D)target zoom:(float)zoom;

/// ### 緯度と経度とズームレベルでZMSCameraPostionを生成する
/// @note `bearing` `viewingAngle`はデフォルト値(0)が設定される。
/// @param latitude: 緯度
/// @param longitude: 経度
/// @param zoom: ズームレベル
/// @return カメラ位置情報
+ (instancetype)cameraWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude zoom:(float)zoom;

/// ### 座標とその他カメラプロパティでZMSCameraPostionを生成する
/// @param target: 座標(緯度/経度)
/// @param zoom: ズームレベル
/// @param bearing: 方位角
/// @param viewingAngle: 傾き角度
/// @return カメラ位置情報
+ (instancetype)cameraWithTarget:(CLLocationCoordinate2D)target zoom:(float)zoom bearing:(CLLocationDirection)bearing viewingAngle:(double)viewingAngle;

/// ### 緯度と経度とその他カメラプロパティでZMSCameraPostionを生成する
/// @param latitude: 緯度
/// @param longitude: 経度
/// @param zoom: ズームレベル
/// @param bearing: 方位角
/// @param viewingAngle: 傾き角度
/// @return カメラ位置情報
+ (instancetype)cameraWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude zoom:(float)zoom bearing:(CLLocationDirection)bearing viewingAngle:(double)viewingAngle;

/// ### 緯度と経度とその他カメラプロパティでZMSCameraPostionを生成する
/// @param latitude: 緯度
/// @param longitude: 経度
/// @param bearing: 方位角
/// @param zoom: ズームレベル
/// @return カメラ位置情報
+ (instancetype)cameraWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude bering:(CLLocationDirection)bearing zoom:(float)zoom __attribute__ ((deprecated));

/// :nodoc:
- (instancetype)init __attribute__((unavailable("init is not available")));

@end

NS_ASSUME_NONNULL_END
