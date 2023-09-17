# ND-77-newcomer

## cpp-kyopro-Library

オレオレライブラリです。

### Algebra
代数に関連するアルゴリズム・データ構造です。

> #### Prime
> 素数に関連するアルゴリズム・データ構造です。

>> ##### Enum_divisors.hpp
>> 約数を列挙します。

>> ##### Factorize.hpp
>> 素因数分解をします。

>> ##### Is_Prime.hpp
>> 素数か判定します。

>> ##### Miller_Rabin.hpp
>> ミラー・ラビン素数判定法で確率的に素数か判定します。

>> ##### Sieve.hpp
>> エラトステネスの篩を作ります。

> #### Comb.hpp
> 場合の数のクラスです。
> 階乗・順列・組み合わせ・重複組合せが扱えます

> #### Fraction.hpp
> 分数クラスです。
> 四則演算と不等号・等号、標準出力が扱えます。

> #### Mod_pow.hpp
> 法を設定した上で繰り返し2乗法によって高速に累乗を求めます。

> #### Modint.hpp
> 合同式を扱います。
> 四則演算と合同、標準出力及び逆元計算と累乗計算が扱えます。

### Graph
グラフに関連するアルゴリズム・データ構造です。

> #### Dijkstra.hpp
> ダイクストラ法で最短経路と最短距離を求めます。

> #### Floyd-Warshall.hpp
> ワーシャルフロイド法で最短距離を求めます。

> #### FordFulkerson.hpp
> フォードファルカーソン法で最大流を求めます。

> #### Topological_sort.hpp
> DAGをトポロジカルソートします。

> #### Weighted_Union_Find.hpp
> 重み付きUnion Find木です。

### macro_templates
マクロやテンプレートです。

> #### template_atcoder.cpp
> AtCoder用のテンプレートです。

> #### templates.cpp
> AtCoder以外にも対応しているテンプレートです。

### String
文字列に関するアルゴリズム・データ構造です。

> #### RollingHash.hpp
> ローリングハッシュをします。

### Geometry.hpp
幾何に関する関数・データ構造です。
使える機能の以下の通りです。

|名前|説明|
|:-:|:-:|
|equal|epsを考慮した等号|
|unitVec|単位ベクトル|
|normalVec|法線ベクトル|
|dot|内積|
|cross|外積|
|rotate|回転|
|rotate_90|90度回転|
|radian_to_degree|弧度法から度数法変換|
|degree_to_radian|度数法から弧度法変換|
|Line|直線|
|Segment|線分|
|Circle|円|
|orthogonal|直行判定|
|parallel|平行判定|
|isPointOnLine|点が直線上に存在|
|isPointOnSegment|点が線分上に存在|
|distance_Line_Point|点と直線の距離|
|distance_Segment_Point|点と線分の距離|
|distance_Segment_Segment|線分と線分の距離|
|CrossPoint|交点|
|ccw|3点の位置関係|
|intersect|交差判定|
|projection|垂線の足|
|reflection|反射|
|inCircle|円の内部に点が存在|
|tangentPoint|ある点を通る円の接線の接点|
|commonTnagentLine|2円の共通接線|
|Inscribed_Circle|内接円|
|Circumscribed_Circle|外接円|
|area|面積|
|convex|多角形の凸判定|
|ConvexHull|凸包|
|contain|多角形に点が含まれるか判定|
|convexCut|多角形の切断|
|convex_Diameter|直径|
|closest_pair|最近点対|

Point,Line,Segment,Circle,Polygon型については標準出力にも対応しています。