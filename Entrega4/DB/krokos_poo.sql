-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 16-06-2023 a las 15:42:48
-- Versión del servidor: 10.6.13-MariaDB-cll-lve
-- Versión de PHP: 8.1.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `krokos_poo`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `BUSQUEDAS`
--

CREATE TABLE `BUSQUEDAS` (
  `usuario` varchar(255) NOT NULL,
  `ultima_busqueda` varchar(255) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Volcado de datos para la tabla `BUSQUEDAS`
--

INSERT INTO `BUSQUEDAS` (`usuario`, `ultima_busqueda`) VALUES
('maximo', 'mouse'),
('pepe', 'luces exterior');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `USUARIOS`
--

CREATE TABLE `USUARIOS` (
  `id_user` int(11) NOT NULL,
  `username` varchar(255) NOT NULL,
  `contrasenia` varchar(255) NOT NULL,
  `nombre` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_spanish_ci NOT NULL,
  `apellido` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_spanish_ci NOT NULL,
  `email` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_spanish_ci NOT NULL,
  `ultimo_intento` datetime NOT NULL,
  `intentos` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Volcado de datos para la tabla `USUARIOS`
--

INSERT INTO `USUARIOS` (`id_user`, `username`, `contrasenia`, `nombre`, `apellido`, `email`, `ultimo_intento`, `intentos`) VALUES
(0, 'maximo', 'maximo', 'Maximo', 'Perez', 'maximo@maximo.com', '2023-06-16 13:30:23', 3),
(1, 'pepe', 'pepe', 'pepe', 'argento', 'pepe@gmail.com', '2023-06-16 12:06:26', 0);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `USUARIOS`
--
ALTER TABLE `USUARIOS`
  ADD PRIMARY KEY (`id_user`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
