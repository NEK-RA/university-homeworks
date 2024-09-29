package ru.mirea.trpp_second_15.entity;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.opencsv.bean.CsvBindByName;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;


/** Сущность сотрудника. */
@Getter
@Setter
@ToString
public class Receipt {

    /** Идентификатор. */
    @JsonProperty("id")
    @CsvBindByName(column = "id")
    private Long id;
    /** email клиента. */
    @JsonProperty("client_email")
    @CsvBindByName(column = "client_email")
    private String clientEmail;
    /** Телефон клиента. */
    @JsonProperty("client_phone")
    @CsvBindByName(column = "client_phone")
    private String clientPhone;
    /** Итоговая сумма. */
    @JsonProperty("amount")
    @CsvBindByName(column = "amount")
    private BigDecimal amount;
    /** Система налогообложения. */
    @JsonProperty("vat")
    @CsvBindByName(column = "vat")
    private String vat;
    /** Доп. реквизит чека. */
    @JsonProperty("additional")
    @CsvBindByName(column = "additional")
    private String additional;

}
