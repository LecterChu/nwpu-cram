drop table customer_lot;
drop table customer;
drop table lot;

create table customer(
 customer_id integer,
 customer_first_name varchar(100),
 customer_last_name varchar(100));

 create table lot(
 lot_id integer,
 lot_description varchar(100),
 lot_size float,
 lot_district integer,
 lot_value float,
 lot_street_address varchar(100));

 create table customer_lot(
 customer_id integer,
 lot_id integer) ;

copy lot from 'd:\\pgdata\\lot.out'; 
copy customer from 'd:\\pgdata\\customer.out';
copy customer_lot from 'd:\\pgdata\\customer_lot.out';

select count(*) from lot;
select relname, reltuples, relpages from pg_class where relname='lot';
select relname, reltuples, relpages from pg_class where relname='customer';
select relname, reltuples, relpages from pg_class where relname='customer_lot';

-- lot 块因子 249999/2688 = 93

-- 查看lot表大小,22020096 单位字节，返回基础存储大小，不包含索引和Toast数据
select pg_relation_size('lot');
-- 使用pg_size_pretty可将单位转换为MB
SELECT pg_size_pretty(pg_relation_size('lot'));

-- 查看block_size页面默认大小 8196

show block_size;

--计算lot表使用页面数 2688
select 22020096/8192;


explain analyze select lot_id from lot ;
/*
"Seq Scan on lot  (cost=0.00..5187.99 rows=249999 width=4) (actual time=0.006..70.975 rows=249999 loops=1)"
"Total runtime: 20.244 ms"

表lot有249999条数据分布在2688个磁盘页， 每个页面块记录数=249999/2688=93 （块因子）

cost=评估开始消耗。这是可以开始输出前的时间，比如排序节点的排序的时间。
     评估总消耗。假设查询从执行到结束的时间。有时父节点可能停止这个过程，比如LIMIT子句。
rows=评估查询节点的输出行数，假设该节点执行结束。
width=评估查询节点的输出行的平均字节数。

actual time=操作节点获取第一行结果的耗时（单位：毫秒）
          操作节点完成所有行处理的耗时。例如 19.975 表示整个过程消耗 19.975ms
rows=查询节点的实际输出行数，假设该节点执行结束。
loops=表示该操作节点（如扫描或连接）被执行的循环次

评估时间是（磁盘页*seq_page_cost）+（扫描行*cpu_tuple_cost）+（扫描行*cpu_operator_cost）*条件数。
默认seq_page_cost是1.0，cpu_tuple_cost是0.01，cpu_operator_cost是0.0025


所以评估值是(2688 * 1.0) + (249999 * 0.01) = 5187.99

*/
show seq_page_cost;
show cpu_tuple_cost;
show cpu_operator_cost;

select (2688 * 1.0) + (249999 * 0.01);

explain analyze select lot_id from lot where lot_id=1 ;
/*
"Seq Scan on lot  (cost=0.00..5812.99 rows=1 width=4) (actual time=0.007..17.151 rows=1 loops=1)"
"  Filter: (lot_id = 1)"
"  Rows Removed by Filter: 249998"
"Total runtime: 17.164 ms"
评估时间是（磁盘页*seq_page_cost）+（扫描行*cpu_tuple_cost）+（扫描行*cpu_operator_cost）*条件数
默认seq_page_cost是1.0，cpu_tuple_cost是0.01，cpu_operator_cost是0.0025
所以评估值是(2688 * 1.0) + (249999 * 0.01)+ (249999 * 0.0025)*1 = 5812.99

*/
select (2688 * 1.0) + (249999 * 0.01)+ (249999 * 0.0025)*1;

explain analyze select lot_id from lot where lot_id=1 or lot_id=2;
/*
"Seq Scan on lot  (cost=0.00..6437.98 rows=2 width=4) (actual time=0.009..20.300 rows=2 loops=1)"
"  Filter: ((lot_id = 1) OR (lot_id = 2))"
"  Rows Removed by Filter: 249997"
"Total runtime: 20.319 ms"
评估值是(2688 * 1.0) + (249999 * 0.01)+ (249999 * 0.0025)*2 = 6437.98
*/

select (2688 * 1.0) + (249999 * 0.01)+ (249999 * 0.0025)*2;



show seq_page_cost;
show cpu_tuple_cost;
--show cpu_filter_cost;
show cpu_operator_cost ;

/*
在 PostgreSQL 中，聚集索引（Clustered Index）与传统数据库系统中的聚集索引概念略有不同，主要是因为 PostgreSQL 主要依赖于表的数据物理顺序来实现所谓的聚集索引效果，而不是像 SQL Server 或 Oracle 那样有专门的聚集索引结构。

在 PostgreSQL 中，可以通过 CLUSTER 命令或者使用 CREATE INDEX 命令时指定 USING btree 并附带 FILLFACTOR 选项来优化表的物理存储顺序，以达到类似聚集索引的效果。

可以使用 CLUSTER 命令来根据一个索引的顺序重新组织表的数据。例如，如果有一个表 employees 和一个索引 emp_name_idx，可以使用CLUSTER employees USING emp_name_idx; 命令将表数据按照这个索引的顺序重新组织，这将使表中的行按照 emp_name_idx 索引的顺序物理存储，从而提高基于该索引的查询性能。

使用 CLUSTER 命令会改变表的物理存储顺序，这可能会影响依赖于原始顺序的应用或查询。在生产环境中使用前应谨慎评估影响。

虽然使用聚集索引可以提高某些查询的性能，但频繁地重建聚集可能会影响插入和更新的性能。因此，应根据实际查询模式和数据更新频率来合理使用。
*/
 



create index lot_size_index on lot using btree(lot_size);
create index lot_size_index on lot using hash(lot_size);
drop index lot_size_index;
explain analyze select lot_id from lot where lot_size between 300 and 15000;


create index lot_value_index on lot using btree(lot_value);
drop index lot_value_index;

explain analyze select lot_id from lot where lot_value between 300 and 15000;


explain analyze select avg(lot_value) from lot;


create index customer_id_index on customer using hash(customer_id);
create index customer_id_index on customer using btree(customer_id);
drop index customer_id_index;
explain analyze select * from customer where customer_id=128888;



 