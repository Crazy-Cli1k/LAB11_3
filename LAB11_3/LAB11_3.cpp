// LAB11_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <windows.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(1251);

    HANDLE hEvent = CreateEvent(0, TRUE, FALSE, TEXT("MySyncRun"));
    if (hEvent)
    {
        if (GetLastError() != ERROR_ALREADY_EXISTS) // первичный запуск
        {
            PROCESS_INFORMATION pi[3];
            memset(pi, 0, sizeof(pi));

            WCHAR fileName[MAX_PATH] = { 0 };
            GetModuleFileName(0, fileName, MAX_PATH);

            cout<<"Запуск процессов..."<<endl;
            for (int i = 0; i < 3; i++)
            {
                STARTUPINFO si;
                memset(&si, 0, sizeof(si));
                if (!CreateProcess(fileName, 0, 0, 0, FALSE, CREATE_NEW_CONSOLE, 0, 0, &si, &pi[i]))
                    cout<<"Ошибка создания процесса!"<<endl;
            }
            cout<<"Сигнал синхронизации"<<endl;
            SetEvent(hEvent);
            cout << "Ожидание завершения работы процессов..." << endl;
            for (int i = 0; i < 3; i++)
            {
                if (pi[i].hProcess)
                    WaitForSingleObject(pi[i].hProcess, INFINITE);
            }
        }
        else // вторичный запуск
        {
            DWORD dwResult;
            cout << "Ожидание синхронизации..." << endl;
            dwResult = WaitForSingleObject(hEvent, INFINITE);
            int B = 1;
            while (B <= 3)
            {
                if (WAIT_FAILED != dwResult)
                {
                    for (int j = 1; j <= 10; j++)
                    {
                        cout << j << endl;
                        Sleep(200);
                    }
                }
                cout << "#### " << B << " ####" << endl;
                B++;
            }

            SetEvent(hEvent);
            cout<<"Работа..."<<endl;
            Sleep(1000);
        }

        CloseHandle(hEvent);
    }
    else
    {
        printf("Ошибка! CreateEvent\n");
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
