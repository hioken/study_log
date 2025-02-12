/**
 * 問題：
 * 反復操作可能なオブジェクトIteratableObject
 * を作成してみましょう。
 * Arrayと同様に以下のメソッドが使用可能とします。
 * 
 * set(key, value)  *1
 * forEach
 * map
 * filter
 * 
 * *1:setはチェーンメソッドとしてつなげられるように実装してみてください。
 * 
 * また、for...ofを使用した際にはMapと同じ挙動を取るものとします。
 * 
 */
class IteratableObject {
	constructor(obj) {
		for(let prop in obj) {
			this[prop] = obj[prop];
		}
	}

	*[Symbol.iterator]() {
		for (const key in this) {
			yield [key, this[key]]
		}
	}

	print(label = '') {
		console.log(`%c ${label}`, 'color: blue; font-weight: 600;', this);
		return this;
	}

	set(key, value) {
		this[key] = value;
		return this;
	}

	forEach(cb) {
		for (const key in this) {
			cb.call(this, this[key])
		}
	}

  map(callback) {
    const newInstance = new MyArray();
    for (let i = 0; i < this.length; i++) {
      const result = callback(this[i], i, this);
      newInstance.push(result);
    }
    return newInstance;
  }

  filter(callback) {
    const newInstance = new MyArray();
    for (let i = 0; i < this.length; i++) {
      if (callback(this[i], i, this)) {
        newInstance.push(this[i]);
      }
    }
    return newInstance;
  }
}

function prefix(v, i, obj) {
	return 'prefix-' + v;
}

const original = new IteratableObject({
	key1: 'value1',
	key2: 'value2',
	key3: 'value3',
});

const result = original
	.map(prefix)
	.set('key4', 'value4')
	.filter(function (val, key) {
		return key === 'key4';
	});

console.log('%coriginal', 'color: blue; font-weight: bold;', original);
console.log('%cresult', 'color: red; font-weight: bold;', result);
/**
 * 期待する出力結果
 * original 
 * {key1: "value1", key2: "value2", key3: "value3"}
 * 
 * result 
 * {key4: "value4"}
 */
