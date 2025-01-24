# exportとimport
## 概要
- exportで関数(や式)を公開する(デフォルトは非公開(private))
- default exportという、呼び出し元で好きな変数に格納出来るexportを設定できる 
```js
import {exportされている関数が格納された変数} from 'library'
import 任意の変数名 form library
