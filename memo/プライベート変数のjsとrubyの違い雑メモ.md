```js
function Counter() {
  let count = 0;

  this.increment = function() {
    return ++count;
  };
}

const counter = new Counter();
console.log(counter.increment()); // 1
console.log(counter.increment()); // 2
```

```ruby
def make_counter
  count = 0
  Proc.new do
    count += 1
  end
end

counter = make_counter
puts counter.call # 1
puts counter.call # 2
puts counter.call # 3
```
これらの違いは
- js
  - 単純に関数にcount変数情報を保存している
  - これは関数より内部のスコープでしかアクセスできない
  - そのため、このコードの場合、関数内で定義した無名関数からしかアクセスできない
- ruby
  - Proc生成時点でcount変数がキャプチャされる
  - このcountはProcによってキャプチャされているため、メモリ上には残っている
  - しかしコード上だとメソッド読み込み終了時点でcount変数にアクセスする方法は消滅している
  - つまり実質的にProcからしかcountにアクセスする手段が残されていない