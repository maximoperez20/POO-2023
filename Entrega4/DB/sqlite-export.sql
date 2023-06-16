--
-- Archivo generado con SQLiteStudio v3.4.4 el Fri Jun 16 16:39:22 2023
--
-- Codificación de texto usada: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Tabla: usuarios
DROP TABLE IF EXISTS usuarios;

CREATE TABLE IF NOT EXISTS usuarios (
    id      INTEGER      PRIMARY KEY,
    usuario VARCHAR (30),
    clave   VARCHAR (30) 
);

INSERT INTO usuarios (
                         id,
                         usuario,
                         clave
                     )
                     VALUES (
                         1,
                         'cgomez',
                         '1234'
                     );

INSERT INTO usuarios (
                         id,
                         usuario,
                         clave
                     )
                     VALUES (
                         2,
                         'maximo',
                         'maximo'
                     );


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
