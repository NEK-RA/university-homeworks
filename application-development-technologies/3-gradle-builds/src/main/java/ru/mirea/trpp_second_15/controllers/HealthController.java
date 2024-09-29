package ru.mirea.trpp_second_15.controllers;

import io.micronaut.http.HttpResponse;
import io.micronaut.http.annotation.Controller;
import io.micronaut.http.annotation.Get;

/** Проверка состояния сервера. */
@Controller()
public class HealthController {

    /**
     * Проверить состояние сервера.
     * @return ответ
     * 200 - OK
     */
    @Get
    public HttpResponse<HealthResponse> healthCheck() {
        return HttpResponse.ok(new HealthResponse("ok"));
    }
}
