package ru.mirea.trpp_second_15.controllers;

import com.opencsv.bean.CsvToBeanBuilder;
import io.micronaut.http.HttpResponse;
import io.micronaut.http.annotation.Controller;
import io.micronaut.http.annotation.Get;
import ru.mirea.trpp_second_15.entity.Receipt;

import java.io.InputStreamReader;
import java.util.List;
import java.util.Optional;

/** Контроллер для работы с чеками. */
@Controller("/receipt")
public class ReceiptController {

    /** Список чеков. */
    private final List<Receipt> receiptList;

    /** Конструктор. */
    public ReceiptController() {
        receiptList = new CsvToBeanBuilder<Receipt>(new InputStreamReader(this.getClass().getResourceAsStream("/MOCK_DATA.csv"))).withType(Receipt.class).build().parse();
    }

    /**
     * Получить список чеков.
     * @return список чеков
     */
    @Get()
    public HttpResponse<List<Receipt>> getEmployee() {
        return HttpResponse.ok(receiptList);
    }

    /**
     * Найти чек по идентификатору.
     * @param id идентификатор сотрудника
     * @return Пользователь, если есть, иначе 404 ошибка
     */
    @Get("/{id}")
    public HttpResponse<Receipt> findById(Long id) {
        Optional<Receipt> result = receiptList.stream().filter(it -> it.getId().equals(id)).findAny();
        if (result.isPresent()) {
            return HttpResponse.ok(result.get());
        } else {
            return HttpResponse.notFound();
        }
    }
}
