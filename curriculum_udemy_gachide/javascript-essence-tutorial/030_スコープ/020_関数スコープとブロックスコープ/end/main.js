function a() {
    let b = 0;
    console.log(b);
}

a();

if(true) {
    let c = 1;
    
    let d = function() {
        console.log('d is called');
    }
}

// d();
// console.log(c);


const abc = 1000;
{
    console.log(abc); // 外部スコープは参照可能
}