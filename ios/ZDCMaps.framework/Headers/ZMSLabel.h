//
//  ZMSPoint.h
//  ZDCMaps
//
//  Created by zdc on 2016/03/02.
//  Copyright © 2016年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIkit.h>
#import "ZMSOverlay.h"

NS_ASSUME_NONNULL_BEGIN

/// ## ラベルクラス
/// 地図上に注記やアイコンを重畳する。
@interface ZMSLabel : ZMSOverlay

// MARK: - プロパティー

/// ### 文字列
@property(nonatomic, copy) NSString *text;

/// ### 座標
/// 表示する位置を指定する。
/// @note 緯度 / 経度
@property(nonatomic) CLLocationCoordinate2D anchor;

/// ### フォントサイズ
/// @note 文字列の長さにより最大フォントサイズは異なる。<br>0未満の値は無視される。<br>デフォルト値: 50
@property(nonatomic) CGFloat textSize;

/// ### 文字色
/// @note デフォルト値: #ffffff00
@property(nonatomic) UIColor *textColor;

/// ### 背景色
/// @note デフォルト値: #ffffff00
@property(nonatomic) UIColor *backgroundColor;

/// ### 背景の領域部分の枠線色
/// @note デフォルト値: #ffffff00
@property(nonatomic) UIColor *strokeColor;

/// ### 背景の領域部分の枠線の線幅
/// @note 0未満の値は無視される。<br>デフォルト値: 0
@property(nonatomic) CGFloat strokeWidth;

/// ### 縁取り色
/// @note デフォルト値: #ffffff00
@property(nonatomic) UIColor *edgeColor;

/// ### 縁取り幅
/// @note デフォルト値: 0
@property(nonatomic) CGFloat edgeWidth;

/// ### 背景部分の角丸半径
/// @note デフォルト値: 0
@property(nonatomic) CGFloat cornerSize;

/// ### 背景部分のパディングサイズ
/// @note 0未満の値は無視される。<br>デフォルト値: x: 0, y: 0
@property(nonatomic) CGPoint backgroundPadding;

/// ### 表示角度
/// @note 有効範囲: -180 - 180度 (時計回り)<br>デフォルト値: 0
@property(nonatomic) CGFloat bearing;

/// ### 文字列の描画位置
/// 0 : 記号と注記の中心揃え<br>1 : 記号の右側<br>2 : 記号の左側<br>3 : 記号の上側<br>4 : 記号の下側
/// @note デフォルト値: 4
@property(nonatomic) NSInteger textPosition;

/// ### 書字方向
/// 0 : 横書き<br>1 : 縦書き
/// @note デフォルト値: 0
@property(nonatomic) NSInteger textDirection;

/// ### アイコン画像
/// @note 画像は複数設定可能。
@property(nonatomic) NSArray<UIImage *> *icons;

/// ### 強制描画フラグ
/// YESの場合、他のラベルと重なっても表示が維持される。
/// @note デフォルト値: NO
@property (nonatomic) BOOL force;

// MARK: - メソッド

/// ### 座標とテキストデザイン情報からZMSLabelを作成する
/// @warning 座標が不正な場合はNULLが戻る。
/// @param text: 文字列
/// @param anchor: 座標(緯度/経度)
/// @return ラベル
+ (nullable instancetype)labelWithText:(NSString *)text anchor:(CLLocationCoordinate2D)anchor;

@end

NS_ASSUME_NONNULL_END
