//
//  ZMSUISettings.h
//  ZDCMaps
//
//  Created by zdc on 2014/12/08.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// ## UIコントロールクラス
/// 地図をコントロールするボタンなどのUIを制御する。<br>`ZMSMapView.settings`経由で利用する。
/// @note 初期化不可
@interface ZMSUISettings : NSObject

// MARK: - ジェスチャ

/// ### スクロールジェスチャー
/// このフラグが有効(YES)の場合、スワイプで地図をスクロールさせることができる。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL scrollGestures;

/// ### ズームジェスチャー
/// このフラグが有効(YES)の場合、ダブルタップ・2本指タップやピンチで地図を拡大縮小させることができる。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL zoomGestures;

/// ### 回転ジェスチャー
/// このフラグが有効(YES)の場合、2本指による回転ジェスチャーで地図を回転させることができる。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL rotateGestures;

/// ### ティルトジェスチャー
/// このフラグが有効(YES)の場合、2本指による垂直方向のスワイプで地図を傾けることができる。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL tiltGestures;

/// ### 全てのジェスチャーに対して一括で有効・無効を設定する
/// @note 有効(YES) / 無効(NO)
/// @param enabled: ジェスチャーの有効・無効
- (void)setAllGesturesEnabled:(BOOL)enabled;

// MARK: - スケールバー

/// ### スケールバーの表示フラグ
/// @note 表示(YES) / 非表示(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL scaleBar;

/// ### スケールバーの基準位置
/// @note 有効範囲: スクリーンの左上(0) / スクリーンの右上(1) / スクリーンの右下(2) / スクリーンの左下(3)<br>デフォルト値: 3
@property (nonatomic, assign) NSInteger scaleBarCorner;

/// ### スケールバーの描画位置
/// 基準位置からのパディングを設定する。
/// @note デフォルト値: (x: 0, y: 0)
@property (nonatomic, assign) CGPoint scaleBarPad;

// MARK: - 現在地ボタン

/// ### 現在地ボタンの表示フラグ
/// @note 表示(YES) / 非表示(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL myLocationButton;

/// ### 現在地ボタンの基準位置
/// @note 有効範囲: スクリーンの左上(0) / スクリーンの右上(1) / スクリーンの右下(2) / スクリーンの左下(3)<br>デフォルト値: 3
@property (nonatomic, assign) NSInteger myLocationButtonCorner;

/// ### 現在地ボタンの描画位置
/// 基準位置からのパディングを設定する。
/// @note デフォルト値: (x: 30, y: 50)
@property (nonatomic, assign) CGPoint myLocationButtonPad;

// MARK: - コンパスボタン

/// ### コンパスボタンの表示フラグ
/// @note 表示(YES) / 非表示(NO)<br>デフォルト値: YES
@property (nonatomic, assign) BOOL compassButton;

/// ### コンパスの基準位置
/// @note 有効範囲: スクリーンの左上(0) / スクリーンの右上(1) / スクリーンの右下(2) / スクリーンの左下(3)<br>デフォルト値: 1
@property (nonatomic, assign) NSInteger compassButtonCorner;

/// ### コンパスの描画位置
/// 基準位置からのパディングを設定する。
/// @note デフォルト値: (x: 10, y: 10)
@property (nonatomic, assign) CGPoint compassButtonPad;

// MARK: - 現在地マーカー

/// ### 現在地マーカーの画像
/// 変更する際はこのプロパティーに画像を入れる。
@property(nonatomic, nullable) UIImage *myLocationMarker;

// MARK: - ボタンデザインタイプ

/// ### ボタンデザインタイプ
/// UIのデザインを変更する。(コンパスボタン・現在地ボタン・現在地マーカー・ズームコントロール)
/// @note 有効範囲: 0 - 2<br>デフォルト値: 0
@property (nonatomic, assign) NSInteger buttonType;

// MARK: - 屋内図

// ### 屋内図の有効・無効
// @warning このプロパティーは機能していない。
/// :nodoc:
@property (nonatomic, assign) BOOL indoorEnabled __attribute__ ((deprecated));

// ### 階層選択リストの表示フラグ
// @warning このプロパティーは機能していない。
// @note 表示(YES) / 非表示(NO)<br>デフォルト値: YES
/// :nodoc:
@property (nonatomic, assign) BOOL indoorPicker __attribute__ ((deprecated));

// ### 階層選択リストの基準位置
// @warning このプロパティーは機能していない。
// @note 有効範囲: スクリーンの左上(0) / スクリーンの右上(1) / スクリーンの右下(2) / スクリーンの左下(3)<br>デフォルト値: 3
/// :nodoc:
@property (nonatomic, assign) NSInteger indoorPickerCorner __attribute__ ((deprecated));

// ### 階層選択リストの描画位置
// 基準位置からのスクリーン座標のピクセル値を指定する。
// @warning このプロパティーは機能していない。
// @note デフォルト値: (x: 30, y: 50)
/// :nodoc:
@property (nonatomic, assign) CGPoint indoorPickerPad __attribute__ ((deprecated));

/// :nodoc:
- (instancetype)init __attribute__((unavailable("init is not available")));

@end

NS_ASSUME_NONNULL_END
