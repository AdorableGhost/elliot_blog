-- 用户权限表
create table role(
id uuid not null default uuid_generate_v4(),
name varchar(100) not null ,
role_num int not null  default  1,
enable int not null default 1,
created_at date not null  default  current_timestamp,
updated_at date not null  default  current_timestamp
);

create table user(
id uuid not null default uuid_generate_v4(),
name varchar(100) not null ,
email varchar(100) not null ,
phone varchar(20) not null ,
enable int not null  default 1, -- 1 启用 ,2 ,未启用
password varchar(255) not null ,
role uuid not null references role(id), -- 表 role 的 id 字段
language int not null, -- 表示使用的语言: 1 中文 ,2 English
created_at date not null  default  current_timestamp,
updated_at date not null  default  current_timestamp,
avatar bytea
);


create table token(
id uuid not null default uuid_generate_v4(),
token uuid not null default uuid_generate_v4(),
created_at date not null  default  current_timestamp,
updated_at date not null  default  current_timestamp,
available_until date not null  default current_timestamp
);

-- 文章类型

create table category(
id uuid not null default uuid_generate_v4(),
name varchar(100) not null ,
describe varchar(1000) not null ,
parent_node uuid references category(id), -- 父亲节点,根节点为null
child_node  uuid[] references category(id), -- 孩子节点集合,是个数组
role_level int not null default 1, -- 阅读权限,只有特殊主题才会有这个权限.比如管理员的私人日记?,通过这个也可以实现隐藏主题
created_at date not null  default  current_timestamp,
updated_at date not null  default  current_timestamp,
avatar bytea
);

-- 文章
create table article(
id uuid not null default uuid_generate_v4(),
name varchar(1000) not null ,
describe varchar(1000) not null ,
category uuid references category(id), -- 所属类别
avatar bytea, -- 头像
content text,
viewed_count bigint not null default 0,
tags uuid[] references tag(id),
role_level int not null default 1, -- 阅读权限,只有特殊主题才会有这个权限.比如管理员的私人日记?,通过这个也可以实现隐藏主题
created_at date not null  default  current_timestamp,
updated_at date not null  default  current_timestamp
);