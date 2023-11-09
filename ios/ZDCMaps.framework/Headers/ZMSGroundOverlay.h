//
//  ZMSGroundOverlay.h
//  ZDCMaps
//
//  Created by zdc on 2016/02/12.
//  Copyright © 2016年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIkit.h>
#import "ZMSOverlay.h"

@class ZMSCoordinateBounds;

NS_ASSUME_NONNULL_BEGIN

/// ## グラウンドオーバーレイクラス
/// 地図上に画像を重畳する。
@interface ZMSGroundOverlay : ZMSOverlay

// MARK: - プロパティー

/// ### 座標
/// 画像の基準の座標。
/// @note 緯度 / 経度
@property(nonatomic) CLLocationCoordinate2D position;

/// ### 画像
/// @note NULLの場合は何も表示されない。
@property(nonatomic, nullable) UIImage *icon;

/// ### 表示角度
/// `position` を基準に画像を回転させる。
/// @note `position` は `anchor` により変動する。<br>有効範囲: 0 - 360度 (時計回り)<br>デフォルト値: 0<br>有効範囲を超えた分は循環し、360度以内に正規化される。
@property(nonatomic) CLLocationDirection bearing;

/// ### 画像の重心
/// この値によって `position` の位置が変わり、`bearing` で回転する際の基準点になる。
/// @note 有効範囲: x: 0.0 - 1.0, y: 0.0 - 1.0<br>デフォルト値: x: 0.5, y: 0.5<br>画像の左上が原点[0.0, 0.0]、[1.0, 1.0]は画像の右下になる。<br>有効範囲を超えた分は有効範囲内に正規化される。
@property(nonatomic) CGPoint anchor;

/// ### 領域
/// 画像を表示する地図上の領域。
@property(nonatomic, nullable) ZMSCoordinateBounds *bounds;

// MARK: - メソッド

/// ### 領域と画像からZMSGroundOverlayを作成する
/// @warning 領域か画像が不正な場合はNULLが戻る。
/// @param bounds: 領域
/// @param icon: 画像
/// @return グラウンドオーバーレイ
+ (nullable instancetype)groundOverlayWithBounds:(ZMSCoordinateBounds *)bounds icon:(nullable UIImage *)icon;

/// ### 座標と画像とズームレベルからZMSGroundOverlayを作成する
/// 指定されたズームレベルで地図を表示した際に、指定された画像のサイズとスクリーン上のサイズが一致するように設置される。<br>指定された座標が画像の中心となるように配置される。
/// @warning 座標か画像かズームレベルが不正な場合はNULLが戻る。
/// @note ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param position: 座標(緯度/経度)
/// @param icon: 画像
/// @param zoomLevel: ズームレベル
/// @return グラウンドオーバーレイ
+ (nullable instancetype)groundOverlayWithPosition:(CLLocationCoordinate2D)position icon:(nullable UIImage *)icon zoomLevel:(CGFloat)zoomLevel;

@end

NS_ASSUME_NONNULL_END
