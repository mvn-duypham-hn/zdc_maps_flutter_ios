//
//  ZMSMarker.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZMSOverlay.h"

NS_ASSUME_NONNULL_BEGIN

/// ## マーカークラス
/// 地図上にマーカーを重畳する。
@interface ZMSMarker : ZMSOverlay

// MARK: - プロパティー

/// ### 座標
/// 表示する位置を指定する。
/// @note 緯度 / 経度
@property(nonatomic) CLLocationCoordinate2D position;

/// ### インフォウィンドウのスニペットのテキスト
@property(nonatomic, copy, nullable) NSString *snippet;

/// ### 任意のマーカー画像
/// ユーザーが指定した画像でマーカーを重畳する。
/// @note NULLの場合はデフォルトのマーカー画像が設定される。
@property(nonatomic, nullable) UIImage *icon;

/// ### 表示角度
/// 回転軸を中心に回転させる。
/// @note 有効範囲: 0 - 360度 (時計回り)<br>デフォルト値: 0<br>有効範囲を超えた分は循環し、360度以内に正規化される。
@property(nonatomic) CLLocationDegrees rotation;

/// ### 回転軸
/// 表示角度が設定された際の重心を設定する。<br>画像サイズに対する割合で設定する。<br>画像の左上が原点[0.0, 0.0]、[1.0, 1.0]は画像の右下になる
/// @note 有効範囲: x: 0.0 - 1.0, y: 0.0 - 1.0<br>デフォルト値: (x: 0.5, y: 1.0)<br>有効範囲を超えた分は有効範囲内に正規化される。
@property(nonatomic) CGPoint groundAnchor;

/// ### インフォウィンドウの表示位置
/// マーカー画像のどの位置にインフォウィンドウを表示させるか指定する。<br>マーカー画像のサイズに対する割合で設定する。<br>マーカー画像の左上が原点[0.0, 0.0]、[1.0, 1.0]はマーカー画像の右下になる。
/// @note 有効範囲: x: 0.0 - 1.0, y: 0.0 - 1.0<br>デフォルト値: (x: 0.5, y: 0.0)<br>有効範囲を超えた分は有効範囲内に正規化される。
@property(nonatomic) CGPoint infoWindowAnchor;

/// ### 透明度
/// @note 有効範囲: 0.0 - 1.0 (0.0は完全に透過)<br>デフォルト値: 1.0
@property(nonatomic) float opacity;

/// ### 座標からZMSMarkerを作成する
/// @warning 座標が不正な場合はNULLが戻る。
/// @param position: 座標(緯度/経度)
/// @return マーカー
+ (nullable instancetype)markerWithPosition:(CLLocationCoordinate2D)position;

@end

NS_ASSUME_NONNULL_END
