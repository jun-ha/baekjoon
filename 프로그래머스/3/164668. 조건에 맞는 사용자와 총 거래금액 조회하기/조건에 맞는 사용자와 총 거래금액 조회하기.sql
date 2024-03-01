SELECT
    U.USER_ID,
    U.NICKNAME,
    G.TOTAL_SALES
FROM
    USED_GOODS_USER U
JOIN
    (SELECT
        WRITER_ID,
        SUM(PRICE) AS TOTAL_SALES
    FROM
        USED_GOODS_BOARD
    WHERE
        STATUS = 'DONE'
    GROUP BY
        WRITER_ID
    HAVING
        TOTAL_SALES >= 700000) G ON U.USER_ID=G.WRITER_ID
ORDER BY
    TOTAL_SALES ASC;