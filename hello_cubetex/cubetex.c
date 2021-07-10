SVECTOR modelCube_mesh[] = {
    {20.0,19.999998807907104,-20.0},
    {20.0,-20.0,-20.0},
    {-20.00000238418579,-19.999996423721313,-20.0},
    {-19.999992847442627,20.000007152557373,-20.0},
    {20.000009536743164,19.99998927116394,20.0},
    {19.99998688697815,-20.000011920928955,20.0},
    {-20.000007152557373,-19.999992847442627,20.0},
    {-19.999998807907104,20.0,20.0}
};

SVECTOR modelCube_normal[] = {
    0.0,-0.0,-1.0,0,
    0.0,0.0,1.0,0,
    1.0,0.0,-2.384185791015625e-07,0,
    -8.940696716308594e-08,-1.0,-2.9802325229866256e-07,0,
    -1.0,2.384185791015625e-07,-1.4901158351676713e-07,0,
    2.6822084464583895e-07,1.0,2.3841852225814364e-07,0,
    0.0,0.0,-1.0,0,
    0.0,-0.0,1.0,0,
    1.0,-5.662441253662109e-07,3.2782537573439186e-07,0,
    -4.768372150465439e-07,-1.0,8.940690321423972e-08,0,
    -1.0,2.0861631355728605e-07,-1.1920931797249068e-07,0,
    2.0861631355728605e-07,1.0,1.7881397695873602e-07,0
};

SVECTOR modelCube_uv[] = {
    83.71398162841797,83.71389770507812, 0, 0,
    125.03179168701172,42.396141052246094, 0, 0,
    83.71398162841797,42.396141052246094, 0, 0,
    125.03179168701172,83.71392059326172, 0, 0,
    83.71398162841797,125.03166770935059, 0, 0,
    125.03179168701172,125.03169059753418, 0, 0,
    1.0784510374069214,83.71392059326172, 0, 0,
    42.39619445800781,125.03169059753418, 0, 0,
    42.39621353149414,83.71392440795898, 0, 0,
    42.39621353149414,125.03166770935059, 0, 0,
    83.71398162841797,83.71392440795898, 0, 0,
    42.39621353149414,83.71390151977539, 0, 0,
    42.39619445800781,1.0783309936523438, 0, 0,
    1.0784281492233276,42.39611053466797, 0, 0,
    42.39619445800781,42.39612579345703, 0, 0,
    42.39619064331055,83.71392059326172, 0, 0,
    1.0784281492233276,42.396141052246094, 0, 0,
    1.0784281492233276,83.71392059326172, 0, 0,
    83.71398162841797,83.71389770507812, 0, 0,
    125.03179168701172,83.71390151977539, 0, 0,
    125.03179168701172,42.396141052246094, 0, 0,
    125.03179168701172,83.71392059326172, 0, 0,
    83.71399688720703,83.71392440795898, 0, 0,
    83.71398162841797,125.03166770935059, 0, 0,
    1.0784510374069214,83.71392059326172, 0, 0,
    1.0784281492233276,125.03169059753418, 0, 0,
    42.39619445800781,125.03169059753418, 0, 0,
    42.39621353149414,125.03166770935059, 0, 0,
    83.71398162841797,125.03169059753418, 0, 0,
    83.71398162841797,83.71392440795898, 0, 0,
    42.39619445800781,1.0783309936523438, 0, 0,
    1.0784281492233276,1.0783309936523438, 0, 0,
    1.0784281492233276,42.39611053466797, 0, 0,
    42.39619064331055,83.71392059326172, 0, 0,
    42.39619445800781,42.396141052246094, 0, 0,
    1.0784281492233276,42.396141052246094, 0, 0
};

CVECTOR modelCube_color[] = {
    255,255,255, 0,
    255,255,255, 0,
    255,0,251, 0,
    255,255,255, 0,
    255,5,7, 0,
    255,255,255, 0,
    255,255,255, 0,
    255,255,255, 0,
    4,18,255, 0,
    255,5,7, 0,
    255,255,255, 0,
    255,255,255, 0,
    254,255,23, 0,
    122,255,107, 0,
    255,255,255, 0,
    255,255,255, 0,
    255,255,255, 0,
    254,255,94, 0,
    255,255,255, 0,
    35,255,11, 0,
    255,255,255, 0,
    255,255,255, 0,
    255,255,255, 0,
    255,5,7, 0,
    255,255,255, 0,
    255,5,7, 0,
    255,255,255, 0,
    255,5,7, 0,
    255,255,255, 0,
    255,255,255, 0,
    254,255,23, 0,
    255,255,255, 0,
    122,255,107, 0,
    255,255,255, 0,
    54,65,255, 0,
    255,255,255, 0
};

int modelCube_index[] = {
    0,2,3,
    7,5,4,
    4,1,0,
    5,2,1,
    2,7,3,
    0,7,4,
    0,1,2,
    7,6,5,
    4,5,1,
    5,6,2,
    2,6,7,
    0,3,7
};

TMESH modelCube = {
    modelCube_mesh,
    modelCube_normal,
    modelCube_uv,
    modelCube_color,
    12
};

extern unsigned long _binary____TIM_cubetex_tim_start[];
extern unsigned long _binary____TIM_cubetex_tim_end[];
extern unsigned long _binary____TIM_cubetex_tim_length;

TIM_IMAGE tim_cube;
