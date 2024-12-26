# CASE
## 概要
- 他のプログラム言語にあるようなCASE式
- いつものcase 対象 when 値の他に、case when 式という風に記述して、else ifのように扱える
- 式なので引数等にも使える
- CASE WHEN 評価式 THEN 式(戻り値) \n WHEN ~ \n ELSE 式(戻り値) END
  - ELSEは省略不可(MySQLの場合)
  - 可能なDBMSも多いが、非推奨
```sql
SELECT item_name, 
  CASE
    WHEN genre = 'appetizer' THEN 'A' || genre
    WHEN genre = 'main' THEN 'B' || genre
    WHEN genre = 'dessert' THEN 'C' || genre
  END AS step
FROM menus;
```

## 例その2
- このジャンルの平均が全体の平均より高い場合
- このジャンルの平均より、このレコードが高い場合
```sql
select name, genre,
  case
    when
      (select avg(selling) from items as t2 where t1.genre = t2.genre) > (select avg(selling) from items)
    then
      '高級品'
    else
      '凡用品'
  end as price_genre
from items as t1;

select name, genre,
  case
    when
      selling > (select avg(selling) from items as t2 where t1.genre = t2.genre)
    then
      '高め'
    else
      '安め'
  end as price_genre
from items as t1;
```
