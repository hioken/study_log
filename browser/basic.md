# ページ遷移
## 最適化
### bfcache
#### 概要
- bf(back/foward)時、DOM,JSの状態(以下ページ状態)をスナップショットから復元
#### イベント
##### 対象
| イベント名 | タイミング | bfcache復帰時の動作 | 主な用途 / 注意点 |
|-------------|-------------|----------------------|--------------------|
| **pageshow** | ページが「表示された」直後 | 発火。`event.persisted === true` で bfcache復帰を判定可 | 復帰時の再初期化・再接続処理に最適 |
| **pagehide** | ページが「隠れる」「離脱する」直前 | 発火（bfcache対象でも）。ただし非同期や重い処理は間に合わない | タイマー停止・軽い状態保存などに使用 |
| **visibilitychange** | タブの表示/非表示が切り替わった時 | 復帰時にも再発火 | UIの一時停止・再開などに利用（完全な離脱検知は不可） |
| **popstate** | 履歴エントリが変わった時（戻る/進む） | bfcache復帰時にも発火する場合あり | SPAやHistory API操作時に利用 |
| **turbo:before-cache** | TurboがDOMをキャッシュする直前 | 発火（bfcacheとは独立だが概念的に近い） | キャッシュ前の軽いDOM整形に使用 |

##### 非対象
| イベント名 | タイミング | bfcache復帰時の動作 | 主な用途 / 注意点 |
|-------------|-------------|----------------------|--------------------|
| **beforeunload** | ページ離脱直前（古い仕様） | 発火するが bfcacheを**無効化**する恐れあり | 可能な限り使用しない（confirm用途以外NG） |
| **unload** | ページ破棄時（古い仕様） | bfcache復帰では**呼ばれない** | ページ完全破棄時のみ発火（非推奨） |
| **DOMContentLoaded** | 初回ロード完了時 | bfcache復帰では**呼ばれない** | 通常遷移専用イベント |
| **load** | ページ全体（画像含む）読み込み完了 | bfcache復帰では**呼ばれない** | 初回レンダリング完了確認用のみ |
| **turbo:load** | Turboナビゲーション後に新ページ読み込み完了 | bfcache復帰では**呼ばれない** | 通常ナビゲーションの初期化用 |

# Web API
## イベント
### 概要
- 出来事の発生をオブジェクト化して、登録済みのハンドラ関数へ配送する仕組み
- オブジェクトの要素
  - 発火タイミング
  - 対象
  - キャンセルの可否
  - 伝播の阻止の可否
  - 実行タイミング
### 動作
1. イベントのキャッチ
2. eventオブジェクトの生成
3. targetを決める
4. 伝播経路を計算
5. リスナーを順に呼ぶ
### 伝播
- Capturing phase: 上（window/document）→下（target）へ降りてくる
- Target phase: ターゲットで処理
- Bubbling phase: 下（target）→上へ戻っていく
### Eventクラス
#### 主要プロパティ
| 項目                     | 内容                                                              |
| ---------------------- | --------------------------------------------------------------- |
| `event.target`         | イベントの発生元として扱われるオブジェクト（通常は最も内側の要素）。`EventTarget`。                |
| `event.currentTarget`  | 現在実行中のリスナが登録されているオブジェクト。`EventTarget`。                          |
| `event.eventPhase`     | 伝播フェーズを示す数値。`CAPTURING_PHASE` / `AT_TARGET` / `BUBBLING_PHASE`。 |
| `event.composedPath()` | 伝播経路を配列として返す。                                                   |

#### クラス
| クラス             | 内容                           | 主な追加情報（例）                                                        |
| --------------- | ---------------------------- | ---------------------------------------------------------------- |
| `Event`         | すべてのイベントの基底クラス。              | `type`, `bubbles`, `cancelable`, `defaultPrevented`, `timeStamp` |
| `UIEvent`       | UI関連イベントの基底クラス。              | `view`, `detail`                                                 |
| `MouseEvent`    | マウス入力由来のイベント。                | `clientX`, `clientY`, `button`, `buttons`, 修飾キー                  |
| `PointerEvent`  | ポインタ入力（マウス/ペン/タッチ）を統一したイベント。 | `pointerId`, `pointerType`, `pressure`                           |
| `KeyboardEvent` | キーボード入力由来のイベント。              | `key`, `code`, `repeat`, 修飾キー                                    |
| `FocusEvent`    | フォーカス遷移に関するイベント。             | `relatedTarget`                                                  |
| `InputEvent`    | 入力の変化に関するイベント。               | `inputType`, `data`                                              |

#### カスタム
```js
const ev = new Event(type, {
  bubbles: true|false,
  cancelable: true|false,
  composed: true|false
});

const ev = new CustomEvent(type, {
  detail: any,
  bubbles: true|false,
  cancelable: true|false,
  composed: true|false
});
```