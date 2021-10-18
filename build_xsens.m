% Save current dir and cd to script dir
startdir = pwd ;
cd(fileparts(mfilename('fullpath')));

generate_folder = 'auto_generated';
mkdir(generate_folder);

addpath([pwd '/' generate_folder]);


def = legacy_code('initialize');

def.IncPaths = {[pwd '/inc']};
def.SrcPaths = {[pwd '/src']};

def.HeaderFiles   = {'sci_xsens.hpp','xsens.h','serialkey.h'};
def.SourceFiles = {'xsens.cpp','serialkey.cpp'};

def.SFunctionName = 'ex_sfun_sci_xsens';
% Start

%def.StartFcnSpec = strcat('void init_xsens(void **work1, uint8 p1[], uint32 size(p1, 1), ', ...
%                           'uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, ', ...
%                           'uint32 p7, uint32 p8, uint32 p9, uint32 p10, uint32 p11, ', ...
%                           'uint32 p12, uint32 p13)');

%def.StartFcnSpec = strcat('void init_xsens(void **work1, uint8 p1[], uint32 size(p1, 1), ', ...
%                           'uint32 p2[10], uint32 size(p2, 1), uint32 p3, uint32 p4)');

def.StartFcnSpec = strcat('void init_xsens(void **work1, uint8 p1[], uint32 size(p1, 1), ', ...
                           'uint8 p2[], uint32 size(p2, 1), uint8 p3[], uint32 size(p3, 1), uint8 p4[], uint32 size(p4, 1), ', ...
                           'uint8 p5[], uint32 size(p5, 1), uint8 p6[], uint32 size(p6, 1), ', ...
                           'uint8 p7[], uint32 size(p7, 1), uint8 p8[], uint32 size(p8, 1), uint8 p9[], uint32 size(p9, 1), ', ...
                           'uint8 p10[], uint32 size(p10, 1), uint8 p11[], uint32 size(p11, 1), ', ...
                           'uint32 p12, uint32 p13)');

% Output
def.OutputFcnSpec = 'void output_xsens(void **work1, double y1[160], double y2[160], double y3[160], double y4[160], double y5[160], double y6[160], double y7[160], double y8[160], double y9[160], double y10[160])';

% Terminate
def.TerminateFcnSpec = 'void terminate_xsens(void **work1)';

def.Options.language = 'C++';

% def.SampleTime = 0.01;
def.SampleTime    = 'parameterized';

def.LibPaths = {'/usr/local/lib/xsens/lib'};
def.HostLibFiles = {'libxsensdeviceapi.so','libxstypes.so'}; %for the mex function
def.TargetLibFiles = {'libxsensdeviceapi.so', 'libxstypes.so'}; %for the generated code


cd(generate_folder);
try
    % generates the rtwmakecfg.m which contains the library and path references
    legacy_code('rtwmakecfg_generate', def);

    %generates the tlc file which is necessary for code generation
    legacy_code('sfcn_tlc_generate', def);

    % generates the corresponding C-MEX S-function:
    legacy_code('sfcn_cmex_generate', def);

    % compiles the generated C-MEX S-function:
    legacy_code('compile', def, {'-I/usr/local/include/xsens','-I/usr/local/lib/xsens/lib64', '-I/usr/local/include', '-lstdc++', '-lm', '-lpthread'});
    % legacy_code('compile', def);
catch exception
    msgString = getReport(exception);
    disp(msgString);
    warnString = 'ERROR DURING COMPILATION OF XSENS BLOCK';
    warning(warnString);
    fid = fopen('build.log','a');
    fprintf(fid, '\n%s\n%s\n', warnString, msgString);
    fclose(fid);
    cd(startdir);
    return;
end

cd(startdir);
