
#include"Waves.h"

void envelope(vector<double>::iterator signal_start, vector<double>::iterator signal_end, vector<double>::iterator hilbert_start, vector<double>::iterator hilbert_end)
{
	for(int i=0; i<signal_end-signal_start;i++)
	{
		*(signal_start+i)=sqrt(pow(*(signal_start+i),2)+pow(*(hilbert_start+i),2));
	}
}

WavesResult* Waves::compute(ResultKeeper *rkp)const {

	vector<double> *ECGBaselineData;
	vector<double> *RPeaksData;
	/*
	ECGBaselineData = rkp.GetResultECGBaseline.GetECGBaselineData(); /// Przypisanie danych ECGBaseline na ktorych beda wykonywane obliczenia
	RPeaksData = rkp.GetResultRPeaks.GetRPeaksData(); /// Przypisanie danych RPeaks na ktorych beda wykonywane obliczenia
	*/

	WavesResult  ResultHolder = WavesResult();///stworz obiekt rezultatu
	ResultHolder.SetWavesResultData(WavesData);////Przypisz dane z klasy liczacej do danych klasy z klasy rezultatu

	return ResultHolder.getResult();// Zwroc odpowiedni wskaünik
}

void Waves::set_qrs_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	//onset_vector1 = costam;
	const float low_freq_lim = 0.5; //porownac te gowna z raportem
	const float hi_freq_lim = 40;
	double a_t_max, env_t=0.0, a_t=0.0;
	int window_qrs_onset=ceil(0.1*sampling_frequency);
	int sliding_win_start,s2=0,tp_int=0,w=0,temp_j=0,win_end=0;
	vector<double> envelope_win, qrs_onset_it;
	vector<double>::const_iterator tp, envelope_end, envelope_start;
	vector<double> signal(ECGBaselineData.end()-ECGBaselineData.begin()),hilbert(ECGBaselineData.end()-ECGBaselineData.begin());
	//2 LINIE PONIZEJ BEDZIE CHYBA MOZNA WYJEBAC, BO JAK NA RAZIE NIC Z TEGO NIE KORZYSTA
	//fft_filter(ECGBaselineData.begin(), ECGBaselineData.end(), signal.begin(), signal.end(),sampling_frequency,low_freq_lim,hi_freq_lim);
	//hilbert_transform(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
	envelope(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
	envelope_end=signal.end();
	envelope_start=signal.begin();
	//vector<double>::const_iterator ecg_baseline_start = ECGBaselineData.begin(); //sprawdzic. tu widac, jaki to typ danych
	//double gowno = ECGBaselineData.at(0); // wyjebac
	for(int i=0; i<RPeaksData.end()-RPeaksData.begin(); i++)
	{
		if (!((RPeaksData.at(i)-ECGBaselineData.at(0))-window_qrs_onset < 0))
		{
			a_t_max=-HUGE_VAL; //bylo: -INFINITY; czy mozna tak sobie zmienic...?
			sliding_win_start=RPeaksData.at(i)-ECGBaselineData.at(0)-window_qrs_onset;
			for(int j=RPeaksData.at(i)-ECGBaselineData.at(0)-1;j>=sliding_win_start;j--)
			{
				if (j+window_qrs_onset>envelope_end-envelope_start) // WSZYSTKO NIZEJ: CZY NIE TRZEBA ZAMIENIAC . NA -> ?
					win_end=envelope_end-envelope_start;
				else
					win_end=j+window_qrs_onset;
				envelope_win.clear();
				a_t=0;
				for(int k=j;k<=win_end;k++)
					envelope_win.push_back(*(envelope_start+k));
				env_t=*(envelope_start+j);
				tp=(envelope_win.begin());
				for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
				{
					a_t+=*it-env_t;
					if (*tp<*it)
						tp=it;
				}
				if (a_t_max<a_t)
				{
					a_t_max=a_t;
					s2=j;
					tp_int=tp-envelope_win.begin()+j-1;
				}
			}
			w=tp_int-s2;
			a_t_max=-HUGE_VAL; //POPRAWIC?
			for(int j=(RPeaksData.at(i)-ECGBaselineData.at(0))-1;j>=s2;j--)
			{
				a_t=0;
				envelope_win.clear();
				for(int k=j;k<=j+w;k++)
					envelope_win.push_back(*(envelope_start+k));
				env_t=*(envelope_start+j);
				for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
				{
					a_t+=*it-env_t;
				}
				if (a_t_max<a_t)
				{
					a_t_max=a_t;
					temp_j=j;
				}
			}
			if (temp_j!=0){
				qrs_onset_it.push_back(ECGBaselineData.at(0)+temp_j);
			}
		}
		// return nie powinno byc??? -> zmienilem na void, jest spoko?
	}
}

	void Waves::set_qrs_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
		const float low_freq_lim = 5;
		const float hi_freq_lim = 30;
		double a_t_max, env_t=0.0, a_t=0.0;
		int window_qrs_end=ceil(0.1*sampling_frequency);
		int sliding_win_end,s2=0,tp_int=0,w=0,temp_j=-1;
		vector<double> envelope_win;
		vector<double>::const_iterator tp, envelope_end, envelope_start;
		vector<double> signal(ECGBaselineData.end()-ECGBaselineData.begin());
		vector<double> hilbert(ECGBaselineData.end()-ECGBaselineData.begin()); // DO CZEGO TO KURWA JEST
		//fft_filter(ECGBaselineData.begin(), ECGBaselineData.end(), signal.begin(), signal.end(),sampling_frequency,low_freq_lim,hi_freq_lim);
		//hilbert_transform(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
		envelope(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
		envelope_end=signal.end();
		envelope_start=signal.begin();
		for(int i=0; i<RPeaksData.end()-RPeaksData.begin(); i++)
		{
			if (!((RPeaksData.at(i)-ECGBaselineData.at(0))+window_qrs_end > envelope_end-envelope_start))
			{
				a_t_max=-HUGE_VAL;
				sliding_win_end=(RPeaksData.at(i)-ECGBaselineData.at(0))+window_qrs_end;
				for(int j=(RPeaksData.at(i)-ECGBaselineData.at(0))+1;j<=sliding_win_end;j++)
				{
					envelope_win.clear();
					if (j-window_qrs_end<0)
					{
						for(int k=0;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					else
					{
						for(int k=j-window_qrs_end;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					a_t=0;
					env_t=*(envelope_start+j);
					tp=(envelope_win.begin());
					for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
					{
						a_t+=*it-env_t;
						if (*tp<*it)
						{
							tp=it;
						}
					}
					if (a_t_max<a_t)
					{
						a_t_max=a_t;
						s2=j;
						tp_int=tp-envelope_win.begin()+j-envelope_win.size();
					}
				}
				w=s2-tp_int;
				a_t_max=-HUGE_VAL;
				for(int j=(RPeaksData.at(i)-ECGBaselineData.at(0))+1;j<=s2;j++)
				{
					a_t=0;
					envelope_win.clear();
					if (j-w<0)
					{
						for(int k=0;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					else
					{
						for(int k=j-w;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					env_t=*(envelope_start+j);
					for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
					{
						a_t+=*it-env_t;
					}
					if (a_t_max<a_t)
					{
						a_t_max=a_t;
						temp_j=j;
					}
				}
				if (temp_j!=-1)
				{
					qrs_end_it.push_back(ECGBaselineData.begin()+temp_j); //CO POETA MIAL NA MYSLI? o_O
				}
			}
		}
}
		/*
		const vector<vector<double>::const_iterator> & Waves::get_qrs_begin() //TO POETA MIAL NA MYSLI :D, glupie, zmienic na get_qrs_end
		{
		return qrs_end_it; //z tego beda korzystac kolejne funkcje
		}
		*/
		void Waves::set_p_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){

			double Rv;
			double mediana=0;
			double Pmax=0;
			int P_mid;
			int ipeak=0;
			int poczatek;
			QVector<int> window_length;
			QVector<double> PToneset;
			QVector<double> dPToneset;
			QVector<double> window_signal;
			QVector<double> onset_signal;
			QVector<double> Pt;
			QVector<double> M;
			int p_one_end_window=ceil(0.1*sampling_frequency);
			for(int i=0;i<RPeaksData.size()-1;i++)
			{
				window_length.push_back(ceil(0.25*((RPeaksData.at(i+1)-ECGBaselineData.at(0))-(RPeaksData.at(i)-ECGBaselineData.at(0)))));
			}
			if((qrs_onset_it.at(0)-ECGBaselineData.begin())>(RPeaksData.at(0)-ECGBaselineData.at(0))) //jesli qrs_end_it jest dobrze, to tez bedzie dzialac
			{
				poczatek=0;
			}
			else
				poczatek=1;
			for(int i=0;i<window_length.size();i++)
			{
				Rv=0.003;
				for(int j=0;j<window_length.at(i);j++)
				{
					window_signal.push_back(ECGBaselineData.at(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)+j));
				}
				for(int j=0;j<window_signal.size();j++)
				{
					mediana+=window_signal.at(j);
				}
				mediana/=window_length.at(i);
				for(int j=0;j<window_signal.size();j++)
				{
					window_signal.replace(j,window_signal.at(j)-mediana); //czyzby problem bo vector zamiast QVector...?
					Pt.push_back(atan(window_signal.at(j)/Rv));
					M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
				}
				mediana=0;
				for(int j=0;j<Pt.size();j++)
				{
					if(Pmax<=Pt.at(j))
					{
						Pmax=Pt.at(j);
						ipeak=j+1;
					}
				}
				if(ipeak==1||ipeak==Pt.size())
				{
					window_signal.clear();
					Pt.clear();
					Pmax=0;
					M.clear();
					continue;
				}
				if((M.at(ipeak-2)<M.at(ipeak-1))&&(M.at(ipeak-1)>M.at(ipeak)))
				{
					P_mid=ipeak+(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i));
					Rv=0.005;
					for(int j=P_mid-p_one_end_window;j<P_mid;j++)
					{
						onset_signal.push_back(ECGBaselineData.at(j));
						mediana+=onset_signal.last();
					}
					mediana/=onset_signal.size();
					for(int j=0;j<onset_signal.size();j++)
					{
						onset_signal.replace(j,onset_signal.at(j)-mediana);
					}
					mediana=0;
					for(int j=0;j<onset_signal.size();j++)
					{
						PToneset.push_back(atan(onset_signal.at(j)/Rv));
						if(j==0)
							continue;
						else
						{
							dPToneset.push_back(PToneset.at(j)-PToneset.at(j-1));
							if(dPToneset.last()>0.07)
							{
								p_onset_it.push_back(ECGBaselineData.begin()+P_mid-p_one_end_window+j);
								break;
							}
						}
					}
				}
				window_signal.clear();
				onset_signal.clear();
				Pt.clear();
				M.clear();
				PToneset.clear();
				dPToneset.clear();
				Pmax=0;
			}
	}
	/*
	const vector<vector<double>::const_iterator> & Waves::get_p_onset() //TO POETA MIAL NA MYSLI :D
	{
	return p_onset_it; //z tego beda korzystac kolejne funkcje
	}
	*/
	void Waves::set_p_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
		double Rv;
		double mediana=0;
		double Pmax=0;
		int P_mid;
		int ipeak;
		int poczatek;
		int window=0;
		QVector<int> window_length; //dojebalem QVectory, zobaczymy czy bedzie budowal BUDUJE W CHUJ :D
		QVector<double> PTend;
		QVector<double> dPTend;
		QVector<double> window_signal;
		QVector<double> onset_signal;
		QVector<double> Pt;
		QVector<double> M;
		int p_one_end_window=ceil(0.1*sampling_frequency);
		for(int i=0;i<RPeaksData.size()-1;i++)
		{
			window_length.push_back(ceil(0.25*((RPeaksData.at(i+1)-ECGBaselineData.at(0))-(RPeaksData.at(i)-ECGBaselineData.at(0)))));
		}
		if((qrs_onset_it.at(0)-ECGBaselineData.begin())>(RPeaksData.at(0)-ECGBaselineData.at(0)))
		{
			poczatek=0;
		}
		else
			poczatek=1;
		for(int i=0;i<window_length.size();i++)
		{
			Rv=0.003;
			for(int j=0;j<window_length.at(i);j++)
			{
				window_signal.push_back(ECGBaselineData.at(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)+j));
			}
			for(int j=0;j<window_signal.size();j++)
			{
				mediana+=window_signal.at(j);
			}
			mediana/=window_length.at(i);
			for(int j=0;j<window_signal.size();j++)
			{
				window_signal.replace(j,window_signal.at(j)-mediana);
				Pt.push_back(atan(window_signal.at(j)/Rv));
				M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
			}
			mediana=0;
			for(int j=0;j<Pt.size();j++)
			{
				if(Pmax<=Pt.at(j))
				{
					Pmax=Pt.at(j);
					ipeak=j+1;
				}
			}
			if(ipeak==1||ipeak==Pt.size())
			{
				window_signal.clear();
				Pt.clear();
				Pmax=0;
				M.clear();
				continue;
			}
			if((M.at(ipeak-2)<M.at(ipeak-1))&&(M.at(ipeak-1)>M.at(ipeak)))
			{
				P_mid=ipeak+(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i));
				if(P_mid+p_one_end_window-1>qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()) //nie powinno byc {} ??
					window=(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin())-P_mid+1;
				else
					window=p_one_end_window;
				Rv=0.005;
				for(int j=P_mid-1;j<P_mid+window-1;j++)
				{
					onset_signal.push_back(ECGBaselineData.at(j));
					mediana+=onset_signal.last();
				}
				mediana/=onset_signal.size();
				for(int j=0;j<onset_signal.size();j++)
				{
					onset_signal.replace(j,onset_signal.at(j)-mediana);
					PTend.push_back(atan(onset_signal.at(j)/Rv));
				}
				mediana=0;
				for(int j=onset_signal.size();j>0;j--)
				{
					if(j==(onset_signal.size()))
						continue;
					else
					{
						dPTend.push_front(PTend.at(j-1)-PTend.at(j));
					}
				}
				for(int j=dPTend.size();j>0;j--)
				{
					if(dPTend.at(j-1)>0.07)
					{
						p_end_it.push_back(ECGBaselineData.begin()+P_mid+j-2);
						break;
					}
				}
			}
			window_signal.clear();
			onset_signal.clear();
			Pt.clear();
			M.clear();
			PTend.clear();
			dPTend.clear();
			Pmax=0;
		}
	}