-- 用户权限表
create table role
(
    id uuid not null primary key default uuid_generate_v4(),
    name varchar(100) not null,
    role_num int not null default 1,
    enable bool not null default true,
    created_at date not null default current_timestamp,
    updated_at date not null default current_timestamp
);

create table users
(
    id uuid not null primary key default uuid_generate_v4(),
    name varchar(100) not null,
    email varchar(100) not null,
    phone varchar(20) not null,
    enable bool not null default true,
    -- 1 启用 ,2 ,未启用
    password varchar(255) not null,
    role uuid not null references role (id),
    -- 表 role 的 id 字段
    language int not null,
    -- 表示使用的语言: 1 中文 ,2 English
    rsa_private text not null,
    rsa_public text not null,
    created_at date not null default current_timestamp,
    updated_at date not null default current_timestamp,
    avatar bytea
);


create table token
(
    id uuid not null primary key default uuid_generate_v4(),
    token uuid not null default uuid_generate_v4(),
    created_at date not null default current_timestamp,
    updated_at date not null default current_timestamp,
    available_until date not null default current_timestamp
);

-- 文章类型

create table category
(
    id uuid not null primary key default uuid_generate_v4(),
    name varchar(100) not null,
    describe varchar(1000) not null,
    parent_node uuid references category (id),
    -- 父亲节点,根节点为null
    child_node uuid
    [],                                       -- 孩子节点集合,是个数组
    role_level  int           not null             default 1, -- 阅读权限,只有特殊主题才会有这个权限.比如管理员的私人日记?,通过这个也可以实现隐藏主题
    created_at  date          not null             default current_timestamp,
    updated_at  date          not null             default current_timestamp,
    avatar      bytea
);

    -- 文章
    create table article
    (
        id uuid not null primary key default uuid_generate_v4(),
        name varchar(1000) not null,
        describe varchar(1000) not null,
        category uuid references category (id),
        -- 所属类别
        "ip" VARCHAR(64) NULL DEFAULT NULL,
        "agent" VARCHAR(511) NULL DEFAULT NULL,
        avatar bytea,
        -- 头像
        content text,
        viewed_count bigint not null default 0,
        tags uuid
        [],
    enable       bool                               default true,
    role_level   int           not null             default 1, -- 阅读权限,只有特殊主题才会有这个权限.比如管理员的私人日记?,通过这个也可以实现隐藏主题
    created_at   date          not null             default current_timestamp,
    updated_at   date          not null             default current_timestamp
);

        -- 标签
        create table tag
        (
            id uuid not null primary key default uuid_generate_v4(),
            tag_name varchar(1000) not null,
            created_at date not null default current_timestamp,
            updated_at date not null default current_timestamp
        );

        create table comment
        (
            id uuid not null primary key default uuid_generate_v4(),
            name varchar(1000) not null,
            "ip" VARCHAR(64) NULL DEFAULT NULL,
            "agent" VARCHAR(511) NULL DEFAULT NULL,
            author VARCHAR(511) NULL DEFAULT '游客',
            "mail" VARCHAR(150) NULL DEFAULT NULL,
            avatar bytea,
            -- 头像
            content text,
            parent_node uuid references comment (id),
            enable bool default true,
            created_at date not null default current_timestamp,
            updated_at date not null default current_timestamp
        );


        -- 页面渲染相关表 , 为了能够自定义 页面,每个用户的页面显示为不同的页面,这里嫁了
        -- 页面渲染的表, 为后期 BBS 预留借口
        create table view
        (
            -- 一个view 字段 对应 一个页面需要存在数据库中的 页面的动态数据,主要是页面的 展室类 元素
            -- 数据库存储之后通过 服务器后端返回给前端.
            id uuid not null primary key default uuid_generate_v4(),
            name varchar(100) not null,
            url varchar(100)
            [],
    element    uuid[]       not null, -- 使用的元素的 uuid ,引用自 elements 表
    created_at date         not null             default current_timestamp,
    updated_at date         not null             default current_timestamp
);

            create table elements
            (
                -- 一个view 字段 对应 一个页面需要存在数据库中的 页面的动态数据,主要是页面的 展室类 元素
                -- 数据库存储之后通过 服务器后端返回给前端.
                id uuid not null primary key default uuid_generate_v4(),
                name varchar(100) not null,
                type varchar(100) not null default 'text',
                --  可以是 color ,class , style ,raw_html ,text,json ,image等,统一使用字符串存储
                model varchar(100) not null,
                -- model 对应 vue 中的 model,页面初始化完成之后这个值会被 直接赋予 前端model
                created_at date not null default current_timestamp,
                updated_at date not null default current_timestamp
            );