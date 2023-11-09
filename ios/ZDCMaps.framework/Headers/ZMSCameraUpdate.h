//
//  ZMSCameraUpdate.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

@class ZMSCameraPosition;
@class ZMSCoordinateBounds;

// NS_ASSUME_NONNULL_BEGIN

/// ## カメラ位置更新情報クラス
/// カメラ位置の更新(`-[ZMSMapView moveCamera:]`)・アニメーション(`-[ZMSMapView animateWithCameraUpdate:Duration:]`)等で利用する。
/// @note 初期化不可。
@interface ZMSCameraUpdate : NSObject

// MARK: - メソッド

/// ### ズームレベルを1増やすZMSCameraUpdateを生成する
/// @note 現在のズームレベルが21.0の場合、何も起こらない
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)zoomIn;

/// ### ズームレベルを1減らすZMSCameraUpdateを生成する
/// @note 現在のズームレベルが2.0の場合、何も起こらない
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)zoomOut;

/// ### 現在のズームレベルから任意のレベル分増減させるZMSCameraUpdateを生成する
/// @note ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param delta: 変更分のズームレベル
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)zoomBy:(float)delta;

/// ### 任意のズームレベルへ変更するZMSCameraUpdateを作成する
/// @note 有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)
/// @param zoom: ズームレベル
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)zoomTo:(float)zoom;

/// ### 任意の座標へ移動するZMSCameraUpdateを作成する
/// @param target: 座標(緯度/経度)
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)setTarget:(CLLocationCoordinate2D)target;

/// ### 任意の座標とズームレベルへ移動するZMSCameraUpdateを作成する
/// @note ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)
/// @param target: 座標(緯度/経度)
/// @param zoom: ズームレベル
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)setTarget:(CLLocationCoordinate2D)target zoom:(float)zoom;

/// ### 任意のカメラ位置情報に移動するZMSCameraUpdateを作成する
/// @param camera: カメラ位置情報
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)setCamera:(ZMSCameraPosition *)camera;

/// ### 指定の領域が画面内に収まるように、座標・ズームレベルを移動するZMSCameraUpdateを作成する
/// @note カメラ位置( `ZMSCameraPosition` )の `bearing` / `viewingAngle` はデフォルト値(0)が設定される。<br>ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param bounds: 領域
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)fitBounds:(ZMSCoordinateBounds *)bounds;

/// ### 指定の領域とパディングが画面内に収まるカメラ位置情報(座標・ズームレベル)に更新するZMSCameraUpdateを作成する
/// @note カメラ位置( `ZMSCameraPosition` )の `bearing` / `viewingAngle` はデフォルト値(0)が設定される。<br>ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param bounds: 領域
/// @param padding: パディング
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)fitBounds:(ZMSCoordinateBounds *)bounds withPadding:(CGFloat)padding;

/// ### 指定の領域とパディング(4辺別に指定できる)が画面内に収まるカメラ位置情報(座標・ズームレベル)に更新するZMSCameraUpdateを作成する
/// @note カメラ位置( `ZMSCameraPosition` )の `bearing` / `viewingAngle` はデフォルト値(0)が設定される。<br>ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param bounds: 領域
/// @param edgeInsets: パディング
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)fitBounds:(ZMSCoordinateBounds *)bounds withEdgeInsets:(UIEdgeInsets)edgeInsets;

/// ### スクリーン座標のX,Y方向の移動量を指定し、移動するZMSCameraUpdateを作成する
/// @param dx: X方向への移動量
/// @param dy: Y方向への移動量
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)scrollByX:(CGFloat)dX Y:(CGFloat)dY;

/// ### 指定したスクリーン座標が画面中央にくるように移動し、指定したズームレベルを増減するZMSCameraUpdateを作成する
/// @note スクリーン座標は左上が原点(0, 0)。<br>指定したスクリーン座標を画面の中心に移動する。<br>ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param delta: 変更分のズームレベル
/// @param point: 拡縮中心のスクリーン座標
/// @return カメラ位置更新情報
+ (ZMSCameraUpdate *)zoomBy:(float)delta atPoint:(CGPoint)point;

/// :nodoc:
- (instancetype)init __attribute__((unavailable("init is not available")));

@end

// NS_ASSUME_NONNULL_END
