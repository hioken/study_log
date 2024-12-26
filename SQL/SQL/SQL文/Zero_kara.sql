create table items (
  id int primary key auto_increment,
  name varchar(100) not null,
  genre varchar(32),
  selling int,
  cost int,
  create_at date
);

create table stores(
  id int primary key auto_increment,
  name varchar(100) not null,
  item_id int,
  amount int
);

insert items values
  (default, 'Tシャツ', '衣服', 1000, 500, '2009-09-20'),
  (default, '穴あけパンチ', '事務用品', 500, 320, '2009-09-11'),
  (default, 'カッターシャツ', '衣服', 4000, 2800, NULL),
  (default, '包丁', 'キッチン用品', 3000, 2800, '2009-09-20'),
  (default, '圧力鍋', 'キッチン用品', 6800, 5000, '2009-01-15'),
  (default, 'フォーク', 'キッチン用品', 500, NULL, '2009-09-20'),
  (default, 'おろしがね', 'キッチン用品', 880, 790, '2009-04-28'),
  (default, 'ボールペン', '事務用品', 100, NULL, '2009-11-11')
;

insert stores values
  (default, '東京', 1, 30),
  (default, '東京', 2, 50),
  (default, '東京', 3, 15),
  (default, '名古屋', 2, 30),
  (default, '名古屋', 3, 120),
  (default, '名古屋', 4, 20),
  (default, '名古屋', 6, 10),
  (default, '名古屋', 7, 40),
  (default, '大阪', 3, 20),
  (default, '大阪', 4, 50),
  (default, '大阪', 6, 90),
  (default, '大阪', 7, 70),
  (default, '福岡', 1, 100)
;







start transaction;

  update items
    set selling = selling - 1000
    where name = 'カッターシャツ';

  update items
    set selling = selling + 1000
    where name = 'Tシャツ';

commit;

start transaction;

  update items
    set selling = selling - 1000
    where name = 'カッターシャツ';

  update items
    set selling = selling + 1000
    where name = 'Tシャツ';

rollback;


select count(case when selling <= 1000 then 1 else NULL end) as low, count(case when selling between 1001 and 3000 then 1 else NULL end) as mid from items;


insert items_2 values
  (default, 'Tシャツ', '衣服', 1000, 500, '2009-09-20'),
  (default, '穴あけパンチ', '事務用品', 500, 320, '2009-09-11'),
  (default, 'カッターシャツ', '衣服', 4000, 2800, NULL),
  (9, '手袋', '衣服', 800, 500, NULL),
  (10, 'やかん', 'キッチン用品', 2000, 1700, '2009-09-20')

select name, sum(selling) from (select * from items union all select * from items_2) as t1 group by name;
