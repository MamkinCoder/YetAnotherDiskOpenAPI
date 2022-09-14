DROP SCHEMA IF EXISTS file_schema CASCADE;

CREATE SCHEMA IF NOT EXISTS file_schema;

CREATE TABLE IF NOT EXISTS file_schema.items (
    id TEXT PRIMARY KEY,
    url TEXT,
    parentId TEXT,
    size INT,
    type TEXT,
    FOREIGN KEY (parentId) REFERENCES file_schema.items(id)
);


INSERT INTO file_schema.items(id, url, parentId, size, type)
VALUES ('элемент_1_4', 'file/urlll', null, 234, 'FILE');

INSERT INTO file_schema.items(id, url, parentId, size, type)
VALUES ('элемент_1_6', 'file/urlll', 'элемент_1_4', 234, 'FILE');
