#ifndef STAFFDAO_H
#define STAFFDAO_H

class StaffDao
{
public:
    StaffDao();
    static int pitchDao(int pitch);
    static int durationDao(int duration);
    static int keyDao(int key);
};

#endif // STAFFDAO_H
