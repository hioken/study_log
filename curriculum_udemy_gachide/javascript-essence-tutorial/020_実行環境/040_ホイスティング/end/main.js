a();

function a() {
    let c = 1;

    console.log(c);

    d();
    function d() {
        console.log('d is called');
    }
    console.log('a is called');
}

const b = 0;

console.log(b);

const abc = {
    a: function() {
        console.log(this.b)
        console.log(this.c()) // ここでエラー？
    },
    b: 100
}

// abc.a();

const def = {
    a: this.b(),
    b: function(){
        return 200;
    }
}

console.log('test2');
console.log(def.a);