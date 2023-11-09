//
//  ZMSMapView.h
//  ZMSMapView
//
//  Created by zdc on 2014/12/05.
//  Copyright (c) 2014年 ZENRIN DataCom Co., LTD.. All rights reserved.
//

#ifndef ZMSMapView_ZMSMapView_h
#define ZMSMapView_ZMSMapView_h

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <GLKit/GLKit.h>

#import "ZMSUISettings.h"
#import "ZMSCoordinateBounds.h"

@class ZMSMapView;
@class ZMSCameraPosition;
@class ZMSCameraUpdate;
@class ZMSMarker;
@class ZMSProjection;
@class ZMSIndoorDisplay;
@class ZMSMapLayer;
@class ZMSOverlay;
@class ZMSPolygon;
@class ZMSPolyline;

NS_ASSUME_NONNULL_BEGIN

/// ## 地図イベントのデリゲート
@protocol ZMSMapViewDelegate <NSObject>

@optional

// MARK: - カメライベント

/// ### アニメーションやジェスチャーなどで、カメラの移動が開始される前にコールされる
/// @param mapView: 対象の地図
/// @param gesture: ユーザーによる操作(YES) / コードによる操作(NO)
- (void)mapView:(ZMSMapView *)mapView willMove:(BOOL)gesture;

/// ### アニメーション中やジェスチャー中など、カメラの移動時にコールされる
/// @note 移動中は繰り返し実行される。<br>アニメーション中は全てのカメラ位置で呼ばれるわけではないが、最後のカメラ位置では必ず呼び出される。
/// @param mapView: 対象の地図
/// @param position: カメラ位置情報
- (void)mapView:(ZMSMapView *)mapView didChangeCameraPosition:(ZMSCameraPosition *)position;

/// ### カメラの移動が完了した後、アイドル状態になった際にコールされる
/// @param mapView: 対象の地図
/// @param position: カメラ位置情報
- (void)mapView:(ZMSMapView *)mapView idleAtCameraPosition:(ZMSCameraPosition *)position;

// MARK: - タップイベント

/// ### 任意の位置をタップした際にコールされる
/// @note マーカー選択時は呼び出されないが、マーカが非選択状態になる際は呼び出される。
/// @param mapView: 対象の地図
/// @param coordinate: 座標(緯度/経度)
- (void)mapView:(ZMSMapView *)mapView didTapAtCoordinate:(CLLocationCoordinate2D)coordinate;

/// ### 地図上の任意の位置を長押しするとコールされる
/// @param mapView: 対象の地図
/// @param coordinate: 座標(緯度/経度)
- (void)mapView:(ZMSMapView *)mapView didLongPressAtCoordinate:(CLLocationCoordinate2D)coordinate;

/// ### マーカーがタップされるとコールされる
/// 戻り値によってマーカーの選択状態を制御できる。
/// @note デフォルト値: NO
/// @param mapView: 対象の地図
/// @param marker: 対象のマーカー
/// @return マーカーを選択状態にしない(YES) / マーカーを選択状態にする(NO)
- (BOOL)mapView:(ZMSMapView *)mapView didTapMarker:(ZMSMarker *)marker;

/// ### マーカーが選択された際にコールされる
/// このデリゲートでUIViewを返した場合、インフォウィンドウの代わりにそのUIViewが表示される。
/// @param mapView: 対象の地図
/// @param marker: 対象のマーカー
/// @return インフォウィンドウの代わりに表示するUIView
- (nullable UIView *)mapView:(ZMSMapView *)mapView markerInfoWindow:(ZMSMarker *)marker;

/// ### マーカーのインフォウィンドウをタップした際にコールされる
/// @param mapView: 対象の地図
/// @param marker: 対象のインフォウィンドウの親マーカー
- (void)mapView:(ZMSMapView *)mapView didTapInfoWindowOfMarker:(ZMSMarker *)marker;

/// ### マーカーのインフォウィンドウを長押しするとコールされる
/// @param mapView: 対象の地図
/// @param marker: 対象のインフォウィンドウの親マーカー
- (void)mapView:(ZMSMapView *)mapView didLongPressInfoWindowOfMarker:(ZMSMarker *)marker;

/// ### 重畳物をタップした際にコールされる
/// @param mapView: 対象の地図
/// @param overlays: タップされた位置に存在する重畳物のリスト
- (void)mapView:(ZMSMapView *)mapView didTapOverlays:(NSArray *)overlays;

/// ### 重畳物をタップした際にコールされる
/// @warning 廃止予定
/// @param mapView: 対象の地図
/// @param overlay: タップされた位置に存在する重畳物
- (void)mapView:(ZMSMapView *)mapView didTapOverlay:(ZMSOverlay *)overlay __attribute__ ((deprecated));

/// ### 現在地ボタンがタップされた時にコールされる
/// 戻り値によって現在地の移動を制御できる。
/// @note デフォルト値: NO
/// @param mapView: 対象の地図
/// @return 現在地に移動しない(YES) / 現在地に移動する(NO)
- (BOOL)didTapMyLocationButtonForMapView:(ZMSMapView *)mapView;

// MARK: - マップイベント

/// ### 移動範囲外へ出た時にコールされる
/// @param mapView: 対象の地図
/// @param camera: カメラ位置情報
- (void)mapView:(ZMSMapView *)mapView onOutOfArea:(ZMSCameraPosition *)camera;

// MARK: - タッチイベントのプロキシー

/// ### 地図内で発生したタッチイベント(TouchesBegan)をUIスレッド経由で中継する
/// @param mapView: 対象の地図
/// @param touches: タッチ情報
/// @param event: イベント情報
- (void)mapView:(ZMSMapView *)mapView touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;

/// ### 地図内で発生したタッチイベント(TouchesMoved)をUIスレッド経由で中継する
/// @param mapView: 対象の地図
/// @param touches: タッチ情報
/// @param event: イベント情報
- (void)mapView:(ZMSMapView *)mapView touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

/// ### 地図内で発生したタッチイベント(TouchesEnded)をUIスレッド経由で中継する
/// @param mapView: 対象の地図
/// @param touches: タッチ情報
/// @param event: イベント情報
- (void)mapView:(ZMSMapView *)mapView touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;

/// ### 地図内で発生したタッチイベント(TouchesCancelled)をUIスレッド経由で中継する
/// @param mapView: 対象の地図
/// @param touches: タッチ情報
/// @param event: イベント情報
- (void)mapView:(ZMSMapView *)mapView touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

// MARK: - ロケーションイベントのプロキシー(MyLocationManager)

/// ### 現在位置が変化した時にコールされる
/// @param mapView: 対象の地図
/// @param coord: 位置情報
- (void)mapView:(ZMSMapView *)mapView didUpdateLocations:(CLLocationCoordinate2D)coord;

/// ### 端末の向きが変化した時にコールされる
/// @param mapView: 対象の地図
/// @param heading: 端末の向き
- (void)mapView:(ZMSMapView *)mapView didUpdateHeading:(CLLocationDirection)heading;

@end

NS_ASSUME_NONNULL_END

/// ## 地図が描画できるかどうかの問い合わせ結果
/// `-[ZMSMapView checkMapArea:zoom:]` の戻り値
typedef NS_ENUM (NSUInteger, CheckMapAreaResult) {
	/// ### 処理失敗
	Error,
	/// ### 地図を描画できないエリア
	No,
	/// ### 地図を描画できるエリア
	Yes
};

/// ## 地図クラス
/// 地図の生成・表示・コントロールを行うメインクラス。
/// @note ZMSMapViewはメインスレッドから読み込まれ、更新される。<br>ほかのスレッドから呼び出されると、例外や未定義の動作となる。
@interface ZMSMapView : UIView <UIGestureRecognizerDelegate, UITableViewDataSource, UITableViewDelegate>

// MARK: - プロパティー

/// ### 地図イベントのデリゲート
/// イベントの発生を受け取るクラスを設定する。
@property (nonatomic, weak) id <ZMSMapViewDelegate> delegate;

/// ### カメラ位置情報
/// `ZMSCameraPosition` のインスタンス。<br>地図のカメラ位置を取得する。
@property (nonatomic, readonly) ZMSCameraPosition *camera;

/// ### 座標とスクリーン座標情報
/// `ZMSProjection` のインスタンス。<br>緯度・経度座標とスクリーン座標関連の処理を行う。
@property (nonatomic, readonly) ZMSProjection *projection;

/// ### 位置情報のバックグラウンド取得フラグ
/// true、または指定なしの場合はバックグラウンドでも取得する。falseの場合はフォアグラウンド時のみ取得する。
@property (nonatomic, readonly) BOOL onlyForegroundLocationUpdatesAllowed;

/// ### 現在地取得の有効化
/// このフラグが有効(YES)で、ユーザーが現在地取得を許可した場合、現在地の取得を開始し、地図上に現在地を示すマーカーが表示される。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: NO
@property (nonatomic, assign, getter=isMyLocationEnabled) BOOL myLocationEnabled;

/// ### 現在地の位置情報
/// 現在地取得が無効の場合やユーザーが現在地取得を許可していない場合は場合はNULLが返る。<br>
/// 値を設定した場合に、現在地の取得を停止し、現在地マーカーが指定した位置に表示される。<br>
/// ユーザー指定の現在地の変更を解除したい場合はNULLを設定する。
@property (nonatomic, nullable) CLLocation *myLocation;

/// ### ヘディングアップモードの有効化
/// このフラグが有効(YES)の場合、端末の位置情報・向きに合わせて、`camera` が常時更新される。
/// @note 有効(YES) / 無効(NO)<br>デフォルト値: NO
@property (nonatomic) BOOL headingUp;

/// ### 選択されているマーカー
/// 選択されているマーカーを取得したり、設定したマーカーを選択状態にする。
/// @note 何も選択されていない場合はNULLが戻る。<br>NULLを設定した場合マーカーの選択状態が解除される。
@property (nonatomic, nullable, strong) ZMSMarker *selectedMarker;

/// ### マップタイプ
/// 地図のデザインを取得・設定する。
@property (nonatomic) NSString *mapType;

/// ### 地図タイプリスト
/// 設定できるマップタイプの一覧を取得する。
@property (nonatomic, readonly) NSArray<NSString *> *mapTypeList;

/// ### 最小ズームレベル (読み取り専用)
@property (nonatomic, assign, readonly) float minZoom;

/// ### 最大ズームレベル (読み取り専用)
@property (nonatomic, assign, readonly) float maxZoom;

// ### 屋内図表示の有効化
// @note 屋内図を表示(YES) / 屋内図を非表示(NO)<br>デフォルト値: NO
/// :nodoc:
@property (nonatomic, assign, getter=isIndoorEnabled) BOOL indoorEnabled;

/// ### UIの制御 (読み取り専用)
/// `ZMSUISettings` のインスタンス。<br>ジェスチャーの有効・無効、コンパスボタン・現在地ボタン・スケールバー・現在地マーカーの表示状況・表示位置などを変更する。
 @property (nonatomic, readonly) ZMSUISettings *settings;

/// ### パディングの設定
/// 地図の4辺にパディングを設定する。<br>パディングはUIの表示位置、地図の中心に影響する。
/// @note UI(コンパスボタン・現在地ボタン等)は地図の表示領域からパディングを除いた領域に配置される。<br>同様にパディングを除いた領域の中心部分がカメラ位置の座標になる。
@property (nonatomic, assign) UIEdgeInsets padding;

/// :nodoc:
@property(nonatomic, readonly, retain) ZMSMapLayer *layer;

// MARK: - メソッド

/// ### 必須パラメーターからZMSMapViewを生成する
/// 地図の生成を行う。
/// @param frame: フレーム
/// @param camera: カメラ位置情報
/// @return 地図
+ (instancetype)mapWithFrame:(CGRect)frame camera:(ZMSCameraPosition *)camera;

/// ### 必須パラメーターからZMSMapViewを生成する
/// 地図の生成を行う。
/// @param frame: フレーム
/// @param camera: カメラ位置情報
/// @param onlyForegroundLocationUpdatesAllowed: バックグラウンドでの位置情報更新を可能にするかどうかのBOOL値。YES: バックグラウンドでの位置情報更新可能, NO: バックグラウンドでの位置情報更新不可
/// @return 地図
+ (instancetype)mapWithFrame:(CGRect)frame camera:(ZMSCameraPosition *)camera onlyForegroundLocationUpdatesAllowed:(BOOL)onlyForegroundLocationUpdatesAllowed;

/// ### 必須パラメーターからZMSMapViewを非同期で生成する
/// 地図の生成を非同期で行う。
/// @param frame: フレーム
/// @param camera: カメラ位置情報
/// @param target: 呼び出し元
/// @param selector: コールバック (地図を受け取る)
+ (instancetype)mapWithFrame:(CGRect)frame camera:(ZMSCameraPosition *)camera target:(id)obj selector:(SEL)mapDidLoad;

/// ### 必須パラメーターからZMSMapViewを非同期で生成する
/// 地図の生成を非同期で行う。
/// @param frame: フレーム
/// @param camera: カメラ位置情報
/// @param target: 呼び出し元
/// @param selector: コールバック (地図を受け取る)
/// @param onlyForegroundLocationUpdatesAllowed: バックグラウンドでの位置情報更新を可能にするかどうかのBOOL値。YES: バックグラウンドでの位置情報更新可能, NO: バックグラウンドでの位置情報更新不可
+ (instancetype)mapWithFrame:(CGRect)frame camera:(ZMSCameraPosition *)camera target:(id)obj selector:(SEL)mapDidLoad onlyForegroundLocationUpdatesAllowed:(BOOL)onlyForegroundLocationUpdatesAllowed;

/// ### 地図に追加されている全ての重畳物を削除する
/// @warning メインスレッドで実行すること。
- (void)clear;

/// ### ズームレベルの最小値と最大値を設定する
/// @note 有効範囲: 2.0 - 21.0<br>`minZoom` > `maxZoom`の場合は無視される。
/// @param minZoom: 最小ズームレベル
/// @param maxZoom: 最大ズームレベル
- (void)setMinZoom:(float)minZoom maxZoom:(float)maxZoom;

/// ### カメラ位置を更新する
/// 指定されたカメラ位置更新情報で現在のカメラ位置を更新する。
/// @param update: カメラ位置更新情報
- (void)moveCamera:(ZMSCameraUpdate *)update;

/// ### カメラ位置情報でアニメーションを実行する
/// 現在のカメラ位置から、指定されたカメラ位置情報まで指定時間でアニメーション移動する。
/// @param cameraPosition: カメラ位置情報
/// @param duration: 時間 (秒)
- (void)animateToCameraPosition:(ZMSCameraPosition *)cameraPosition duration:(double)duration;

/// ### 座標でアニメーションを実行する
/// 現在のカメラ位置から、指定された座標まで指定時間でアニメーション移動する。
/// @param location: 座標(緯度/経度)
/// @param duration: 時間 (秒)
- (void)animateToLocation:(CLLocationCoordinate2D)location duration:(double)duration;

/// ### ズームレベルでアニメーションを実行する
/// 現在のカメラ位置から、指定されたズームレベルまで指定時間でアニメーション移動する。
/// @note ズームレベルの有効範囲: 2.0 - 21.0 (2.0が最も引いた状態)<br>有効範囲を超えた分は有効範囲内に正規化される。
/// @param zoom: ズームレベル
/// @param duration: 時間 (秒)
- (void)animateToZoom:(float)zoom duration:(double)duration;

/// ### 方位角でアニメーションを実行する
/// 現在のカメラ位置から、指定された方位角まで指定時間でアニメーション移動する。
/// @note 有効範囲: 0 - 360度 (時計回り)<br>デフォルト値: 0<br>有効範囲を超えた分は循環し、360度以内に正規化される。
/// @param bearing: 方位角
/// @param duration: 時間 (秒)
- (void)animateToBearing:(CLLocationDirection)bearing duration:(double)duration;

/// ### 傾き角度でアニメーションを実行する
/// 現在のカメラ位置から、指定された傾き角度まで指定時間でアニメーション移動する。
/// @note 有効範囲: 0 - 30度 (0度は地図平面に対して直角)<br>デフォルト値: 0<br>超えた分は有効範囲内に正規化される。
/// @param viewingAngle: 傾き角度
/// @param duration: 時間 (秒)
- (void)animateToViewingAngle:(double)viewingAngle duration:(double)duration;

/// ### カメラ位置更新情報でアニメーションを実行する
/// 現在のカメラ位置を、指定されたカメラ位置更新情報に応じて指定時間をかけてアニメーション移動する。
/// @param update: カメラ位置更新情報
/// @param duration: 時間 (秒)
- (void)animateWithCameraUpdate:(ZMSCameraUpdate *)cameraUpdate duration:(double)duration;

/// ### 移動範囲
/// カメラが移動できる領域を制限する。<br>指定した範囲外には移動できなくなる。
/// @note 指定した領域の左下と右上の緯度・経度が同一の場合、移動範囲の制限は行われない。
/// @param bounds: 領域
- (void)setMovableRegion:(ZMSCoordinateBounds *)bounds;

/// ### コンパスアイコンがタップされていない時の背景画像を設定する
/// @note NULLの場合、デフォルトの画像が設定される。<br>背景部分は地図の回転に連動せず固定表示される。
/// @param image: 画像
- (void)setCompassBackgroundImage:(nullable UIImage *)backgroundImage;

/// ### コンパスアイコンがタップされた時の背景画像を設定する
/// @note NULLの場合、デフォルトの画像が設定される。<br>背景部分は地図の回転に連動せず固定表示される。
/// @param image: 画像
- (void)setCompassBackgroundFocusImage:(nullable UIImage *)backgroundFocusImage;

/// ### コンパスアイコンの針画像を設定する
/// @note NULLの場合、デフォルトの画像が設定される。<br>針画像は地図の回転にともない回転する。
/// @param image: 画像
- (void)setCompassNeedleImage:(nullable UIImage *)needleImage;

/// ### 現在地ボタンがタップされていない時の画像を設定する
/// @note NULLの場合、デフォルトの画像が設定される。
/// @param image: 画像
- (void)setgpsOnImage:(nullable UIImage *)onImage;

/// ### 現在地ボタンがタップされた時の画像を設定する
/// @note NULLの場合、デフォルトの画像が設定される。
/// @param image: 画像
- (void)setgpsFocusImage:(nullable UIImage *)focusImage;

/// ### 指定した座標とズームレベルで地図が描画できるか問い合わせる
/// @note サーバー通信を行うため、ネットワーク状況によっては処理に時間がかかる。<br>非同期で実行される。
/// @param coordinate: 座標(緯度/経度)
/// @param zoom: ズームレベル
/// @return CheckMapAreaResult
- (CheckMapAreaResult)checkMapArea:(CLLocationCoordinate2D)coordinate zoom:(float)zoom;

@end

#endif
