/*

Program yang akan membaca file excel do path "../../data/{nama_file}.xls" kemudian print

*/

#include <stdio.h>
#include <stdlib.h>
#include "..\..\lib\libxls\include\xls.h"

int main() {
    const char* filename = "../../../data/{nama_file}.xls";
    xlsWorkBook* workbook;
    xlsWorkSheet* worksheet;
    xlsCell* cell;

    workbook = xls_open(filename, "UTF-8");
    if (workbook == NULL) {
        printf("Failed to open the Excel file.\n");
        return 1;
    }

    worksheet = xls_getWorkSheet(workbook, 0);
    if (worksheet == NULL) {
        printf("Failed to get the first worksheet.\n");
        xls_close(workbook);
        return 1;
    }

    int row, col;
    for (row = 0; row <= worksheet->rows.lastrow; ++row) {
        for (col = 0; col <= worksheet->rows.lastcol; ++col) {
            cell = xls_cell(worksheet, row, col);
            if (cell != NULL) {
                printf("%s\t", cell->str);
            }
        }
        printf("\n");
    }

    xls_close(workbook);
    return 0;
}