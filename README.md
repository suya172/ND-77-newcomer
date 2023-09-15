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