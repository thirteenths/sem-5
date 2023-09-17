FirstQ = """
SELECT id_worker, fnp, brth
FROM workers
WHERE department = 'Бухгалтерия' AND brth =
                                     (
                                         SELECT MIN(brth)
                                            FROM workers
                                            WHERE department = 'Бухгалтерия'
                                         );
"""

SecondQ = """
SELECT DISTINCT id_worker, COUNT(*)
FROM in_out
WHERE cur_type = 2
GROUP BY id_worker, cur_type
HAVING COUNT(*) > 4;
"""

ThirdQ = """
SELECT workers.id_worker
FROM workers join in_out io on workers.id_worker = io.id_worker
WHERE io.cur_date = now() AND io.cur_type = 1 AND io.cur_time IN
(
    SELECT MAX(cur_time)
    FROM in_out
    WHERE io.cur_type = 1
    );
"""
