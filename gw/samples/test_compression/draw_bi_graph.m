function draw_bi_graph(base_name)

image_precision = 100;
font_size = 16;
line_width = 3;
nbr_test = 12;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Load data

instruc = sprintf('%sL;', base_name);
eval(instruc);
err_linear = l2_error;

instruc = sprintf('%sB;', base_name);
eval(instruc);
err_butterfly = l2_error;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Distortion
plot(bpv, err_linear, 'k', bpv, err_butterfly, 'k:', 'LineWidth',line_width);
title_caption = sprintf('Distortion (image %s)',base_name);
title(title_caption, 'FontWeight','bold', 'FontSize', font_size);
xlabel('Bits per vertex.', 'FontSize', font_size-2)
ylabel('L2 error.', 'FontSize', font_size-2);
legend('Linear transform', 'Butterfly transform');
axis([0,max_bpv,0,err_butterfly(1)]);

file_name = sprintf('%s%s','Distortion_',base_name);
str = sprintf('print -dpng -r%d %s', image_precision, file_name);
eval(str);	% save the image in a png graphic
pause;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PSNR

PSNR_linear 	= 20*log10( sqrt(4*pi)*255./err_linear );
PSNR_butterfly 	= 20*log10( sqrt(4*pi)*255./err_butterfly );


plot(bpv, PSNR_linear, 'k', bpv, PSNR_butterfly, 'k:', 'LineWidth',line_width);
title_caption = sprintf('PSNR (image %s)',base_name);
title(title_caption, 'FontWeight','bold', 'FontSize', font_size);
xlabel('Bits per vertex', 'FontSize', font_size-2)
ylabel('dB', 'FontSize', font_size-2);
legend('Linear transform', 'Butterfly transform');
m = max(max(PSNR_butterfly), max(PSNR_linear));
axis([0,max_bpv,PSNR_butterfly(1)-1,m+2]);

file_name = sprintf('%s%s','PSNR_',base_name);
str = sprintf('print -dpng -r%d %s', image_precision, file_name);
eval(str);	% save the image in a png graphic