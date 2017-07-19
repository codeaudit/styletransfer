
#include <vector>

#include "caffe/layers/loss/gan_softmax_loss_layer.hpp"
#include "caffe/util/math_functions.hpp"

namespace caffe {

template <typename Dtype>
void GANSoftmaxWithLossLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top)
{
	LayerParameter softmax_param(this->layer_param_);
  softmax_param.set_type("Softmax");
  softmax_layer_ = LayerRegistry<Dtype>::CreateLayer(softmax_param);
  softmax_bottom_vec_.clear();
  softmax_bottom_vec_.push_back(bottom[0]);
  softmax_top_vec_.clear();
  softmax_top_vec_.push_back(&prob_);
  softmax_layer_->SetUp(softmax_bottom_vec_, softmax_top_vec_);

}

template <typename Dtype>
void GANSoftmaxWithLossLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) 
{
  softmax_layer_->Reshape(softmax_bottom_vec_, softmax_top_vec_);
  top[0]->Reshape(1,1,1,1);
  if (Caffe::gan_type() == "train_dnet")
  	loss_.Reshape(bottom[0]->num()/2,1,bottom[0]->height(),bottom[0]->width());
  else
  	loss_.Reshape(bottom[0]->num(),1,bottom[0]->height(),bottom[0]->width());
}

INSTANTIATE_CLASS(GANSoftmaxWithLossLayer);
REGISTER_LAYER_CLASS(GANSoftmaxWithLoss);
}  // namespace caffe
