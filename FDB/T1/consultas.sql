-- Todos os gols dos jogadores dos 5 paises com mais artilheiros
SELECT p.nome as Pais, sum(j.totalGols) as totalGols FROM Pais p
    JOIN Jogador j on p.idPais = j.idPais
    GROUP BY p.nome
    ORDER BY totalGols DESC
    LIMIT 5;

-- Jogadores com a melhor média de gols com mais de 10 jogos
SELECT j.nome, (j.totalGols / j.totalPartidas) as mediaGols FROM Jogador j
    WHERE j.totalPartidas > 10
    ORDER BY mediaGols DESC;

-- Países com mais títulos
SELECT P.nome AS Pais, COUNT(PA.idPartida) AS Titulos FROM Partida AS PA
    JOIN Pais AS P ON PA.idGanhador = P.idPais
    WHERE PA.fase = 'Final'
    GROUP BY P.nome
    ORDER BY Titulos DESC;

-- Países com mais vices
SELECT P.nome AS Pais, COUNT(PA.idPartida) AS Vices FROM Partida AS PA
    JOIN Pais AS P ON PA.idPerdedor = P.idPais
    WHERE PA.fase = 'Final'
    GROUP BY P.nome
    ORDER BY Vices DESC;
