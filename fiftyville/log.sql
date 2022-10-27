-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Busca o nome das pessoas
SELECT name FROM people
-- Consulta security logs
WHERE people.license_plate IN (
    -- Pega license plates do courthouse logs
    SELECT license_plate FROM courthouse_security_logs
    -- dentro do período de 10 minutos (10:15 - 10:25)
    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
)
-- Consulta ATM transactions
AND people.id IN (
    -- Pega person_id do ATM transactions
    SELECT person_id FROM bank_accounts
    -- Une com o bank account information  para poder pegar o person_id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    -- Transações do dia do crime
    WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
    -- Cancelado
    AND transaction_type = "withdraw"
    -- Ocorreu na Fifer Street
    AND atm_transactions.atm_location = "Fifer Street"
)
-- Consulta calls
AND people.phone_number IN (
    -- Pega 0 phone numbers de calls
    SELECT caller FROM phone_calls
    -- Data do ccrime
    WHERE year = 2020 AND month = 7 AND day = 28
    -- Que duraram menos de 10 minutos
    AND duration < 60
)
-- Consulta a lista de passageiros do primeiro voo
AND people.passport_number IN (
    -- Pega o número do passaporte dos passageiros
    SELECT passport_number FROM passengers
    -- Dentro do 1º voov
    WHERE flight_id IN (
        -- Pega o id do primeiro voo do próximo dia
        SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29
        ORDER BY hour, minute ASC LIMIT 1
    )
);
-- O ladrão é: Ernest
-- Buscao nome da cidade
SELECT city FROM airports
-- do primeiro voo do dia
WHERE id IN (
    SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29
    ORDER BY hour, minute ASC LIMIT 1
);
--  o ladrão escapou para: London
-- Busca o nome do cúmplice
SELECT name FROM people
-- Usando o número de telefone
WHERE phone_number IN (
    -- da lista de chamadas
    SELECT receiver FROM phone_calls
    -- na data do crime
    WHERE year = 2020 AND month = 7 AND day = 28
    -- onde onde quem ligou era o criminoso
    AND caller = (
        SELECT phone_number FROM people WHERE name = "Ernest"
    )
    -- restringe o resultado para reduzir a probabilidade de obter mais de um resultado
    AND duration < 60
);
-- o cúmplice é: Berthold